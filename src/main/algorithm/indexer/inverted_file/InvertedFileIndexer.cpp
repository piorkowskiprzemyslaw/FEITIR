//
// Created by Przemek Piórkowski on 04.04.2016.
//

#include <set>
#include "InvertedFileIndexer.h"

namespace feitir {
    InvertedFileIndexer::InvertedFileIndexer(const IFParametersPtr &parameters) : Indexer{parameters}, vocabulary{parameters->getVocabulary()} {
        DatabasePtr database = parameters->getDatabase();
        VocabularyTypePtr vocabulary = parameters->getVocabulary();

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
        ImagePtr img = query->getImg();
        std::vector<std::pair<ImagePtr, float>> result;


        return nullptr;
    }

    InvertedFileIndexer::~InvertedFileIndexer() {

    }

    void InvertedFileIndexer::processImage(const ImagePtr img) {
        std::vector<cv::DMatch> matches;
        matcher.match(img->getDescriptors(), vocabulary->getVocabularyMatrix(), matches);

        for (auto match: matches) {
            invertedFile.insert({match.trainIdx, img});
        }
    }

}