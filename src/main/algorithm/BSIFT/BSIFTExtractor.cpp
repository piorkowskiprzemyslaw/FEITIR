//
// Created by Przemek Piórkowski on 25.03.2016.
//

#include "BSIFTExtractor.h"

namespace feitir {

    BSIFTExtractor::~BSIFTExtractor() {

    }

    CategoryPtr BSIFTExtractor::extractBSIFT(const CategoryPtr category) {
        std::vector<ImagePtr> bsiftImages(category->getImages().size());

        for (auto& img : category->getImages()) {
            bsiftImages.push_back(extractBSIFT(img));
        }

        return std::make_shared<Category>(category->getName(), category->getPath(), std::move(bsiftImages));
    }

    DatabasePtr BSIFTExtractor::extractBSIFT(const DatabasePtr database) {
        std::vector<ImagePtr> bsiftImages(database->getImages().size());
        std::vector<CategoryPtr> bsiftCategories(database->getCategories().size());

        for (auto& img : database->getImages()) {
            bsiftImages.push_back(extractBSIFT(img));
        }

        for (auto& cat : database->getCategories()) {
            bsiftCategories.push_back(extractBSIFT(cat));
        }

        return std::make_shared<Database>(database->getRootPath(), std::move(bsiftCategories), std::move(bsiftImages));
    }


}
