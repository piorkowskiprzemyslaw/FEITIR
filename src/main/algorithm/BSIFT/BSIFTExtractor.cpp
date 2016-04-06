//
// Created by Przemek Piórkowski on 25.03.2016.
//

#include "BSIFTExtractor.h"

namespace feitir {

    BSIFTExtractor::~BSIFTExtractor() {

    }

    CategoryPtr BSIFTExtractor::extractCategoryBSIFT(const CategoryPtr category) {
        std::vector<ImagePtr> bsiftImages(category->getImages().size());

        for (auto& img : category->getImages()) {
            bsiftImages.push_back(extractImageBSIFT(img));
        }

        return std::make_shared<Category>(category->getName(), category->getPath(), std::move(bsiftImages));
    }

    DatabasePtr BSIFTExtractor::extractDatabaseBSIFT(const DatabasePtr database) {
        std::vector<ImagePtr> bsiftImages;
        std::vector<CategoryPtr> bsiftCategories;

        for (auto& img : database->getImages()) {
            bsiftImages.push_back(extractImageBSIFT(img));
        }

        for (auto& cat : database->getCategories()) {
            bsiftCategories.push_back(extractCategoryBSIFT(cat));
        }

        return std::make_shared<Database>(database->getRootPath(), std::move(bsiftCategories), std::move(bsiftImages));
    }


}
