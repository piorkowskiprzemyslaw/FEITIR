//
// Created by Przemek Piórkowski on 08.07.2016.
//

#include <unordered_set>
#include "CrossIndexer.h"
#include "src/main/util/Util.h"

namespace feitir {

    CrossIndexer::CrossIndexer(const CrossParametersPtr &parameters)
            : Indexer{parameters},
              parameters{parameters} {
        setupIndexer();
    }

    void CrossIndexer::setupIndexer() {
        // uuidToImg map setup
        // inverted file map setup
        visualWordIndex.clear();
        for (auto img : *(parameters->getDatabase())) {
            auto bsiftImg  = std::dynamic_pointer_cast<ImageBSIFT>(img);
            if (nullptr == bsiftImg)
                throw std::invalid_argument("use database translator to transform database first!");
            uuidToImg.emplace(img->getUuid(), bsiftImg);
            for (auto &match : bsiftImg->getMatches()) {
                visualWordIndex.emplace(match.trainIdx,
                                        std::forward_as_tuple(bsiftImg, bsiftImg->getBsift()[match.queryIdx]));
                codeWordIndex.emplace(generateCodeWord(bsiftImg->getBsift()[match.queryIdx]),
                                      std::forward_as_tuple(match.trainIdx, bsiftImg->getBsift()[match.queryIdx]));
            }
        }

        // nearest visual words setup
        nearestVW.clear();
        matcher.knnMatch(parameters->getVocabulary()->getVocabularyMatrix(),
                         parameters->getVocabulary()->getVocabularyMatrix(),
                         nearestVW, parameters->getN() + 1);

        std::for_each(nearestVW.begin(), nearestVW.end(),
                      [] (std::vector<cv::DMatch>& matches) {
                          matches.erase(matches.begin());
                      });
    }

    CrossResultPtr CrossIndexer::query(CrossQueryPtr query) {
        CrossResultPtr result = std::make_shared<CrossResult>();
        std::unordered_map<boost::uuids::uuid, float> uuidToResult;

        for (auto i = 0; i < query->getImg()->getMatches().size(); ++i) {
            std::unordered_set<int> V;
            std::unordered_set<int> visitedV;
            std::unordered_set<ImageBSIFT::BSIFT> C;
            std::unordered_set<ImageBSIFT::BSIFT> visitedC;
            const auto queryBSIFT = query->getImg()->getBsift()[query->getImg()->getMatches()[i].queryIdx];

            // add n nearest visual words to V map.
            std::for_each(nearestVW[query->getImg()->getMatches()[i].trainIdx].begin(),
                          nearestVW[query->getImg()->getMatches()[i].trainIdx].end(),
                          [&V] (const cv::DMatch &match) {
                              V.insert(match.trainIdx);
                          });

            for (auto & expanded : expandCodeWord(generateCodeWord(query->getImg()->getBsift()[i]))) {
                C.insert(expanded);
            }

            while (!V.empty() && !C.empty()) {
                for (const auto &v : V) {
                    // for each unvisited element
                    if (!Util::contains<int>(visitedV, v)) {
                        auto range = visualWordIndex.equal_range(v);
                        for (auto it = range.first; it != range.second; ++it) {
                            ImageBSIFT::BSIFT bsift;
                            ImageBSIFTPtr imageBSIFTPtr;
                            std::tie(imageBSIFTPtr, bsift) = it->second;

                            if (Util::hammingDistance(bsift, queryBSIFT) <= parameters->getBinaryTreshold()) {
                                auto matchWeight = parameters->getMatchingFunc()(it->first, imageBSIFTPtr->getUuid());

                                if (uuidToResult.find(imageBSIFTPtr->getUuid()) == uuidToResult.end()) {
                                    uuidToResult[imageBSIFTPtr->getUuid()] = 0;
                                }
                                uuidToResult[imageBSIFTPtr->getUuid()] += matchWeight;

                                Util::customInsert(C, visitedC, generateCodeWord(bsift));
                            }
                        }
                        visitedV.insert(v);
                    }
                }

                for (const auto & vv : visitedV) {
                    V.erase(vv);
                }

                for (auto & c : C) {
                    // for each unvisited element
                    if (!Util::contains<ImageBSIFT::BSIFT>(visitedC, c)) {
                        codeWordCellCheck(queryBSIFT, c, V, visitedV);

                        for (auto & expanded : expandCodeWord(c, 1)) {
                            codeWordCellCheck(queryBSIFT, expanded, V, visitedV);
                        }

                        visitedC.insert(c);
                    }
                }

                for (const auto & vc : visitedC) {
                    C.erase(vc);
                }
            }
        }

        for (auto& val : uuidToResult) {
            result->addResultEntry({uuidToImg[val.first], val.second});
        }

        return result;
    }

    void CrossIndexer::codeWordCellCheck(const ImageBSIFT::BSIFT &queryBSIFT, const ImageBSIFT::BSIFT &codeWord,
                                         std::unordered_set<int> &V, std::unordered_set<int> &visitedV) const {
        auto range = codeWordIndex.equal_range(codeWord);
        for (auto it = range.first; it != range.second; ++it) {
            int visualWord;
            ImageBSIFT::BSIFT bsift;
            tie(visualWord, bsift) = it->second;

            if (Util::hammingDistance(bsift, queryBSIFT) <= parameters->getBinaryTreshold()) {
                Util::customInsert(V, visitedV, visualWord);
            }
        }
    }

    ImageBSIFT::BSIFT CrossIndexer::generateCodeWord(const ImageBSIFT::BSIFT &bsift) {
        std::string s;
        boost::to_string(bsift, s);
        return ImageBSIFT::BSIFT(s, 0, parameters->getCodeWordSize());
    }

    std::vector<ImageBSIFT::BSIFT> CrossIndexer::expandCodeWord(const ImageBSIFT::BSIFT &codeWord) {
        return expandCodeWord(codeWord, parameters->getR());
    }

    std::vector<ImageBSIFT::BSIFT> CrossIndexer::expandCodeWord(const ImageBSIFT::BSIFT &codeWord,
                                                                const size_t expansionSize) {
        std::vector<ImageBSIFT::BSIFT> result;
        auto subsets = Util::generateAllSubsets<size_t>(allPositionsSet(), expansionSize);
        std::transform(subsets.begin(), subsets.end(), back_inserter(result),
                       [&codeWord] (const std::set<size_t> &positions) {
                           auto expandedCodeWord = ImageBSIFT::BSIFT(codeWord);
                           for (auto & pos : positions) {
                               expandedCodeWord.flip(pos);
                           }
                           return expandedCodeWord;
                       });
        return result;
    }

    std::set<size_t> CrossIndexer::allPositionsSet() const {
        std::set<size_t> returnSet;
        for (size_t i = 0; i < parameters->getCodeWordSize(); ++i) {
            returnSet.insert(i);
        }
        return returnSet;
    }

    IndexerResultPtr CrossIndexer::query(IndexerQueryPtr queryPtr) {
        return query(std::static_pointer_cast<CrossQuery>(queryPtr));
    }

}
