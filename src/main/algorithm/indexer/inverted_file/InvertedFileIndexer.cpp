//
// Created by Przemek Piórkowski on 04.04.2016.
//

#include <set>
#include "InvertedFileIndexer.h"

namespace feitir {
    InvertedFileIndexer::InvertedFileIndexer(const IFParametersPtr &parameters) : Indexer{parameters} {
        DatabasePtr database = parameters->getDatabase();

        for (auto image : database->getImages()) {
            processImage(image);
        }

        for (auto category : database->getCategories()) {
            for (auto image : category->getImages()) {
                processImage(image);
            }
        }
    }

    IFResultPtr InvertedFileIndexer::query(IFQueryPtr query) {
        std::unordered_map<boost::uuids::uuid, float> uuidToResult;

        IFResultPtr resultPtr = std::make_shared<IFResult>();
        ImagePtr img = query->getImg();
        for (auto& match : img->getMatches()) {
            auto range = invertedFile.equal_range(match.trainIdx);
            for (auto dbImage = range.first; dbImage != range.second; ++dbImage) {
                float currentVal = uuidToResult[dbImage->second->getUuid()];
                uuidToResult[dbImage->second->getUuid()] = currentVal + 1;
            }
        }

        for (auto& val : uuidToResult) {
            resultPtr->addResultEntry({uuidToImageMap[val.first], val.second});
        }

        return resultPtr;
    }

    InvertedFileIndexer::~InvertedFileIndexer() {

    }

    void InvertedFileIndexer::processImage(const ImagePtr img) {
        uuidToImageMap.emplace(img->getUuid(), img);
        for (auto& match : img->getMatches()) {
            invertedFile.emplace(match.trainIdx, img);
        }
    }

}