//
// Created by Przemek Piórkowski on 13.04.2016.
//

#ifndef FEITIR_BINARYINVERTEDFILEINDEXER_H
#define FEITIR_BINARYINVERTEDFILEINDEXER_H

#include <unordered_map>
#include <tuple>
#include "src/main/algorithm/indexer/Indexer.h"
#include "src/main/util/Util.h"
#include "src/main/algorithm/BSIFT/ImageBSIFT.h"
#include "BIFConfig.h"

namespace feitir {

    class BinaryInvertedFileIndexer : public Indexer {
    private:
        const int treshold;
        std::unordered_multimap<int, std::tuple<ImageBSIFTPtr, typename ImageBSIFT::BSIFT>> binaryInvertedFile;
        std::unordered_map<boost::uuids::uuid, ImageBSIFTPtr> uuidToImageMap;

    protected:
        void processImage(ImagePtr img) {
            auto bsiftImg = std::dynamic_pointer_cast<ImageBSIFT>(img);
            if (bsiftImg == nullptr) {
                throw std::invalid_argument("img of type ImagePtr which cannot be casted to ImageBSIFTPtr");
            }

            uuidToImageMap.emplace(bsiftImg->getUuid(), bsiftImg);
            for (auto& match : bsiftImg->getMatches()) {
                binaryInvertedFile.emplace(match.trainIdx, std::make_tuple(bsiftImg, bsiftImg->getBsift()[match.queryIdx]));
            }
        }

    public:
        BinaryInvertedFileIndexer(const BIFParametersPtr &parameters) : Indexer{parameters},
                                                                        treshold{parameters->getTreshold()} {
            DatabasePtr database = parameters->getDatabase();
            for (auto image : *database) {
                processImage(image);
            }
        }

        virtual IndexerResultPtr query(IndexerQueryPtr queryPtr) override {
            return query(std::static_pointer_cast<BIFQuery>(queryPtr));
        }

        virtual IndexerResultPtr query(BIFQueryPtr query) {
            std::unordered_map<boost::uuids::uuid, IndexerResultMap> uuidToResult;
            IndexerResultPtr resultPtr = std::make_shared<IndexerResult>();
            typename ImageBSIFT::BSIFT bsift;
            ImageBSIFTPtr imgPtr;

            auto img = query->getBSIFTImg();
            for (auto& match : img->getMatches()) {
                auto range = binaryInvertedFile.equal_range(match.trainIdx);
                for (auto dbImage = range.first; dbImage != range.second; ++dbImage) {
                    std::tie(imgPtr, bsift) = dbImage->second;
                    if (Util::hammingDistance(img->getBsift()[match.queryIdx], bsift) <= treshold) {

                        if (uuidToResult.find(imgPtr->getUuid()) == uuidToResult.end()) {
                            uuidToResult[imgPtr->getUuid()] = {{match.trainIdx, 1}};
                        } else {
                            uuidToResult[imgPtr->getUuid()][match.trainIdx]++;
                        }
                    }
                }
            }

            for (auto& val : uuidToResult) {
                resultPtr->addResultEntry({uuidToImageMap[val.first], val.second});
            }

            return resultPtr;
        }

    };

    using BinaryInvertedFileIndexerPtr = std::shared_ptr<BinaryInvertedFileIndexer>;

}

#endif //FEITIR_BINARYINVERTEDFILEINDEXER_H
