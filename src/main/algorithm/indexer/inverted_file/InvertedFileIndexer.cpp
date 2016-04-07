//
// Created by Przemek Piórkowski on 04.04.2016.
//

#include <set>
#include "InvertedFileIndexer.h"

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
        IFResultPtr resultPtr = std::make_shared<IFResult>();
        ImagePtr img = query->getImg();
        for (auto& match : img->getMatches()) {
            auto dbImages = invertedFile.find(match.trainIdx);
            while (dbImages != invertedFile.end()) {

            }
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