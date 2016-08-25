//
// Created by Przemek Piórkowski on 15.04.2016.
//

#ifndef FEITIR_SUPPORTINGWORDSINVERTEDFILEINDEXER_H
#define FEITIR_SUPPORTINGWORDSINVERTEDFILEINDEXER_H

#include <iostream>
#include <unordered_map>
#include <opencv/cv.hpp>
#include "src/main/util/Util.h"
#include "src/main/algorithm/indexer/Indexer.h"
#include "src/main/algorithm/BSIFT/ImageBSIFT.h"
#include "SWIFConfig.h"

namespace feitir {

    /**
     * Implementation of binary inverted file indexer which uses supporting words map.
     */
    class SupportingWordsInvertedFileIndexer : public Indexer {
    private:
        cv::BFMatcher matcher;

        // algorithm parameter
        int p;

        // algorithm parameter
        int K;

        // hamming distance threshold below which pair is marked as a match.
        int distanceTreshold;

        // Transformed database - database transformed with vocabulary - does not include original SIFT descriptor
        // value, but includes mapping from particular descriptor to VisualWord.
        DatabasePtr transformedDb;
        VocabularyTypePtr vocabulary;

        // below map contains transformed images - without information about original SIFT descriptor
        std::unordered_map<boost::uuids::uuid, ImageBSIFTPtr> uuidToBSIFTImageMap;

        // inverted file structure
        std::unordered_multimap<int, std::tuple<ImageBSIFTPtr, ImageBSIFT::BSIFT>> invertedFile;

        // supporting words multimap
        std::unordered_multimap<int, int> supportingWordsMap;

    protected:
        void processImage(ImagePtr img) {
            auto bsiftImg = std::dynamic_pointer_cast<ImageBSIFT>(img);
            if (bsiftImg == nullptr) {
                throw std::invalid_argument("img");
            }

            uuidToBSIFTImageMap.emplace(bsiftImg->getUuid(), bsiftImg);
            for (auto match : bsiftImg->getMatches()) {
                invertedFile.emplace(match.trainIdx, std::make_tuple(bsiftImg, bsiftImg->getBsift()[match.queryIdx]));
            }
        }

        void computeSupportingWords() {
            cv::BFMatcher matcher;
            std::vector<cv::DMatch> matches;
            cv::Mat vocabularyMatrix = vocabulary->getVocabularyMatrix();
            assert(vocabularyMatrix.rows >= p);

            for (int i = 0; i < vocabularyMatrix.rows; ++i) {
                matcher.match(vocabularyMatrix, vocabularyMatrix.row(i), matches);

                // find first p matches with smallest distance
                std::nth_element(matches.begin(), matches.begin() + p, matches.end(),
                                 [] (const cv::DMatch &a, const cv::DMatch &b) {
                                     return a.distance < b.distance;
                                 });

                // add each of this p matches to supporting words multimap
                for (auto it = matches.begin(); it != matches.begin() + p; ++it) {
                    supportingWordsMap.emplace(i, it->queryIdx);
                }

                matches.clear();
            }
        }

        std::tuple<cv::Mat, std::unordered_map<int, int>> supportingWordMatrix(int i) {
            assert(i <= supportingWordsMap.size());
            cv::Mat result;
            std::unordered_map<int, int> resultMapping;
            auto range = supportingWordsMap.equal_range(i);
            int currentWord = 0;
            for (auto it= range.first; it != range.second; ++it) {
                result.push_back(vocabulary->getVocabularyMatrix().row(it->second));
                resultMapping.emplace(currentWord++, it->second);
            }
            return std::make_tuple(result, resultMapping);
        }

        std::vector<int> findKNearestVisualWords(cv::Mat queryFeature, int vwIdx, unsigned K) {
            std::vector<cv::DMatch> matches;
            cv::Mat supportingWords;
            std::unordered_map<int, int> resultMapping;
            std::tie(supportingWords, resultMapping)= supportingWordMatrix(vwIdx);
            // match current feature from image with all supporting words of trainIdx visual word.
            matcher.match(supportingWords, queryFeature, matches);
            // find element with smallest distance to the query
            std::nth_element(matches.begin(), matches.begin() + K, matches.end(),
                             [] (const cv::DMatch &a, const cv::DMatch &b) {
                                 return a.distance < b.distance;
                             });

            std::vector<int> result;
            for (auto it = matches.begin(); it != matches.begin() + K; ++it) {
                result.push_back(resultMapping[it->queryIdx]);
            }

            return result;
        }

    public:
        explicit SupportingWordsInvertedFileIndexer(const SWIFParametersPtr &parameters)
                : Indexer{parameters}, transformedDb{parameters->getTransformedDb()},
                  p{parameters->getP()}, distanceTreshold{parameters->getDistanceTreshold()},
                  K{parameters->getK()}, vocabulary{parameters->getVocabulary()} {

            for (auto img : *transformedDb) {
                processImage(img);
            }

            computeSupportingWords();
        }

        virtual IndexerResultPtr query(SWIFQueryPtr query) {
            std::unordered_map<boost::uuids::uuid, IndexerResultMap> uuidToResult;
            IndexerResultPtr resultPtr = std::make_shared<IndexerResult>();
            ImageBSIFTPtr transformedImage = query->getTransformedImage();
            ImagePtr originalImage = query->getOriginalImage();
            ImageBSIFT::BSIFT bsift;
            ImageBSIFTPtr imgPtr;

            for (auto match : transformedImage->getMatches()) {
                cv::Mat qFeature = originalImage->getDescriptors().row(match.queryIdx);
                std::vector<int> nearestVWs =
                        findKNearestVisualWords(qFeature, findKNearestVisualWords(qFeature, match.trainIdx, 1)[0], K);

                for (auto vwIdx : nearestVWs) {
                    auto range = invertedFile.equal_range(vwIdx);
                    for (auto dbImage = range.first; dbImage != range.second; ++ dbImage) {
                        std::tie(imgPtr, bsift) = dbImage->second;
                        auto distance = Util::hammingDistance(transformedImage->getBsift()[match.queryIdx], bsift);
                        if (distance <= distanceTreshold) {

                            if (uuidToResult.find(imgPtr->getUuid()) == uuidToResult.end()) {
                                uuidToResult[imgPtr->getUuid()] = {{vwIdx, 1}};
                            } else {
                                uuidToResult[imgPtr->getUuid()][vwIdx]++;
                            }

                        }
                    }
                }
            }

            for (auto& val : uuidToResult) {
                resultPtr->addResultEntry({uuidToBSIFTImageMap[val.first], val.second});
            }

            return resultPtr;
        }

        virtual ~SupportingWordsInvertedFileIndexer() override = default;

        virtual IndexerResultPtr query(IndexerQueryPtr queryPtr) override {
            return query(std::static_pointer_cast<SWIFQuery>(queryPtr));
        }

    };

    using SupportingWordsInvertedFileIndexerPtr = std::shared_ptr<SupportingWordsInvertedFileIndexer>;

}


#endif //FEITIR_SUPPORTINGWORDSINVERTEDFILEINDEXER_H
