//
// Created by Przemek Piórkowski on 04.04.2016.
//

#include <set>
#include "InvertedFileIndexer.h"

namespace feitir {
    InvertedFileIndexer::InvertedFileIndexer(const IFParametersPtr &parameters)
            : Indexer{parameters}, matchingFunction{parameters->getMatchingFunction()} {
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
                auto matchWeight = matchingFunction(match.trainIdx, dbImage->second->getUuid());
                if (uuidToResult.find(dbImage->second->getUuid()) == uuidToResult.end()) {
                    uuidToResult[dbImage->second->getUuid()] = 0;
                }

                uuidToResult[dbImage->second->getUuid()] += matchWeight;
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