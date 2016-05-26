//
// Created by przemek on 25.05.16.
//

#include "BSIFTExtractor.h"

namespace feitir {

    ImageBSIFTPtr BSIFTExtractor::extractImageBSIFT(const ImagePtr image) {
        assert (image->getDescriptors().rows > 0);
        std::vector<BSIFT> descriptors(image->getDescriptors().rows);

        for (int i = 0; i < image->getDescriptors().rows; ++i) {
            descriptors[i] = processRow(image->getDescriptors().row(i));
        }

        return std::make_shared<ImageBSIFT>(image, getN(), std::move(descriptors));
    }

    CategoryPtr BSIFTExtractor::extractCategoryBSIFT(const CategoryPtr category) {
        std::vector<ImagePtr> bsiftImages;

        for (auto& img : category->getImages()) {
            bsiftImages.push_back(extractImageBSIFT(img));
        }

        return std::make_shared<Category>(category->getName(), category->getPath(), std::move(bsiftImages));
    }

    DatabasePtr BSIFTExtractor::extractDatabaseBSIFT(const DatabasePtr database) {
        std::vector<ImagePtr> bsiftImages;
        std::vector<CategoryPtr> bsiftCategories;

        for (auto img : database->getImages()) {
            bsiftImages.push_back(extractImageBSIFT(img));
        }

        for (auto cat : database->getCategories()) {
            bsiftCategories.push_back(extractCategoryBSIFT(cat));
        }

        return std::make_shared<Database>(database->getRootPath(), std::move(bsiftCategories), std::move(bsiftImages));
    }

    const unsigned int BSIFTExtractor::getN() const {
        return N;
    }

    BSIFTExtractor::DatabaseTranslatorPtr BSIFTExtractor::getDatabaseTranslatorPtr() const {
        return std::make_shared<const BSIFTDatabaseTranslator>();
    }
}