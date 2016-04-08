//
// Created by Przemek Piórkowski on 04.04.2016.
//

#include <set>
#include "InvertedFileIndexer.h"
#include <unordered_map>

namespace feitir {
    InvertedFileIndexer::InvertedFileIndexer(const IFParametersPtr &parameters) : Indexer{parameters}, vocabulary{parameters->getVocabulary()} {
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
        std::unordered_map<boost::uuids::uuid, ImagePtr> uuidToImageMap;
        std::unordered_map<boost::uuids::uuid, float> uuidToResult;

        IFResultPtr resultPtr = std::make_shared<IFResult>();
        ImagePtr img = query->getImg();
        for (auto& match : img->getMatches()) {
            for (auto dbImage = invertedFile.find(match.trainIdx); dbImage != invertedFile.end(); ++dbImage) {
                uuidToImageMap.insert({dbImage->second->getUuid(), dbImage->second});
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
        std::vector<cv::DMatch> matches;
        matcher.match(img->getDescriptors(), vocabulary->getVocabularyMatrix(), matches);
        for (auto& match : img->getMatches()) {
            invertedFile.insert({match.trainIdx, img});
        }
    }

}