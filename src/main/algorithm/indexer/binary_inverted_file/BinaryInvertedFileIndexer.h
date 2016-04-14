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

    template <std::size_t N>
    class BinaryInvertedFileIndexer : public Indexer<BIFResultPtr<N>, BIFQueryPtr<N>, BIFParametersPtr> {
    private:
        const Util util;
        const VocabularyTypePtr vocabulary;
        const std::size_t treshold;
        std::unordered_multimap<int, std::tuple<ImageBSIFTPtr<N>, typename ImageBSIFT<N>::BSIFT>> binaryInvertedFile;
        std::unordered_map<boost::uuids::uuid, ImageBSIFTPtr<N>> uuidToImageMap;

    protected:
        void processImage(const ImageBSIFTPtr<N> img) {
            uuidToImageMap.insert({img->getUuid(), img});
            for (auto& match : img->getMatches()) {
                binaryInvertedFile.insert({match.trainIdx, std::make_tuple(img, img->getBsift()[match.imgIdx])});
            }
        }

    public:
        BinaryInvertedFileIndexer(const BIFParametersPtr &parameters) : Indexer<BIFResultPtr<N>, BIFQueryPtr<N>, BIFParametersPtr>{parameters},
                                                                        vocabulary{parameters->getVocabulary()},
                                                                        treshold{parameters->getTreshold()} {
            DatabasePtr database = parameters->getDatabase();

            for (auto image : database->getImages()) {
                auto bsiftImg = std::dynamic_pointer_cast<ImageBSIFT<N>>(image);
                if (bsiftImg == nullptr)
                    throw std::invalid_argument("database");
                processImage(bsiftImg);
            }

            for (auto category : database->getCategories()) {
                for (auto image : category->getImages()) {
                    auto bsiftImg = std::dynamic_pointer_cast<ImageBSIFT<N>>(image);
                    if (bsiftImg == nullptr)
                        throw std::invalid_argument("database");
                    processImage(bsiftImg);
                }
            }
        }

        virtual BIFResultPtr<N> query(BIFQueryPtr<N> query) {
            std::unordered_map<boost::uuids::uuid, int32_t> uuidToResult;
            BIFResultPtr<N> resultPtr = std::make_shared<BIFResult<N>>();
            typename ImageBSIFT<N>::BSIFT bsift;
            ImageBSIFTPtr<N> imgPtr;

            auto img = query->getImg();
            for (auto& match : img->getMatches()) {
                for (auto dbImage = binaryInvertedFile.find(match.trainIdx); dbImage != binaryInvertedFile.end(); ++dbImage) {
                    std::tie(imgPtr, bsift) = dbImage->second;
                    if (util.hammingDistance(img->getBsift()[match.imgIdx], bsift) <= treshold) {
                        auto currentVal = uuidToResult[imgPtr->getUuid()];
                        uuidToResult[imgPtr->getUuid()] = currentVal + 1;
                    }
                }
            }

            for (auto& val : uuidToResult) {
                resultPtr->addResultEntry({uuidToImageMap[val.first], val.second});
            }

            return resultPtr;
        }

    };

}

#endif //FEITIR_BINARYINVERTEDFILEINDEXER_H
