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
    template <std::size_t N>
    class SupportingWordsInvertedFileIndexer : public Indexer<SWIFResultPtr<N>,  SWIFQueryPtr<N>, SWIFParametersPtr> {
    private:
        cv::BFMatcher matcher;
        const Util util;

        // algorithm parameter
        std::size_t p;

        // algorithm parameter
        std::size_t K;

        // hamming distance treshold which below which we mark pair of features as match.
        std::size_t distanceTreshold;

        // Transformed database - database transformed with vocabulary - does not include original SIFT descriptor
        // value, but includes mapping from particular descriptor to VisualWord.
        DatabasePtr transformedDb;
        VocabularyTypePtr vocabulary;

        // below map contains transformed images - without information about original SIFT descriptor
        std::unordered_map<boost::uuids::uuid, ImageBSIFTPtr<N>> uuidToBSIFTImageMap;

        // inverted file structure
        std::unordered_multimap<int, std::tuple<ImageBSIFTPtr<N>, typename ImageBSIFT<N>::BSIFT>> invertedFile;

        // supporting words multimap
        std::unordered_multimap<int, int> supportingWordsMap;

    protected:
        void processImage(ImagePtr img) {
            auto bsiftImg = std::dynamic_pointer_cast<ImageBSIFT<N>>(img);
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

        std::vector<unsigned> findKNearestVisualWords(cv::Mat queryFeature, unsigned vwIdx, unsigned K) {
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

            std::vector<unsigned> result;
            for (auto it = matches.begin(); it != matches.begin() + K; ++it) {
                result.push_back(resultMapping[it->queryIdx]);
            }

            return result;
        }

    public:
        explicit SupportingWordsInvertedFileIndexer(const SWIFParametersPtr &parameters)
                : Indexer<SWIFResultPtr<N>,  SWIFQueryPtr<N>, SWIFParametersPtr>{parameters},
                  transformedDb{parameters->getTransformedDb()},
                  p{parameters->getP()},
                  distanceTreshold{parameters->getDistanceTreshold()},
                  K{parameters->getK()},
                  vocabulary{parameters->getVocabulary()} {

            for (auto img : *transformedDb) {
                processImage(img);
            }

            computeSupportingWords();
        }

        virtual SWIFResultPtr<N> query(SWIFQueryPtr<N> query) override {
            std::unordered_map<boost::uuids::uuid, int32_t> uuidToResult;
            SWIFResultPtr<N> resultPtr = std::make_shared<SWIFResult<N>>();
            ImageBSIFTPtr<N> transformedImage = query->getTransformedImage();
            ImagePtr originalImage = query->getOriginalImage();
            typename ImageBSIFT<N>::BSIFT bsift;
            ImageBSIFTPtr<N> imgPtr;

            for (auto match : transformedImage->getMatches()) {
                cv::Mat qFeature = originalImage->getDescriptors().row(match.queryIdx);
                std::vector<unsigned> nearestVWs = findKNearestVisualWords(qFeature,
                                                                           findKNearestVisualWords(qFeature,
                                                                                                   match.trainIdx,
                                                                                                   1)[0],
                                                                           K);

                for (auto vwIdx : nearestVWs) {
                    auto range = invertedFile.equal_range(vwIdx);
                    for (auto dbImage = range.first; dbImage != range.second; ++ dbImage) {
                        std::tie(imgPtr, bsift) = dbImage->second;
                        auto distance = util.hammingDistance(transformedImage->getBsift()[match.imgIdx], bsift);
                        if (distance <= distanceTreshold) {
                            auto currentVal = uuidToResult[imgPtr->getUuid()];
                            uuidToResult[imgPtr->getUuid()] = currentVal + 1;
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

    };

}


#endif //FEITIR_SUPPORTINGWORDSINVERTEDFILEINDEXER_H
