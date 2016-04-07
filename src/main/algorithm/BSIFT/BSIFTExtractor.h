//
// Created by Przemek Piórkowski on 25.03.2016.
//

#ifndef FEITIR_BSIFTEXTRACTOR_H
#define FEITIR_BSIFTEXTRACTOR_H

#include <iostream>
#include <vector>
#include "src/main/database/Database.h"
#include "src/main/database/category/Category.h"
#include "src/main/database/image/Image.h"
#include "src/main/algorithm/BSIFT/ImageBSIFT.h"
#include "src/main/algorithm/BSIFT/BSIFTDatabaseTranslator.h"

namespace feitir {

    /**
     * Abstract class representing entity which is able to extract N bits Binary SIFT descriptor value for particular Image.
     */
    template <std::size_t N>
    class BSIFTExtractor {
    public:

        /**
         * Image with Binary SIFT descriptor value.
         */
        using ImageBSIFT = typename feitir::ImageBSIFT<N>;

        /**
         * Binary SIFT descriptor type.
         */
        using BSIFT = typename feitir::ImageBSIFT<N>::BSIFT;

        /**
         * Pointer to image with Binary SIFT descriptor value type.
         */
        using ImageBSIFTPtr = typename feitir::ImageBSIFTPtr<N>;

        /**
         * Pointer to database translator class.
         */
        using DatabaseTranslatorPtr = typename feitir::BSIFTDatabaseTranslatorPtr<N>;

        virtual ~BSIFTExtractor() { }

        virtual ImageBSIFTPtr extractImageBSIFT(const ImagePtr image) = 0;

        virtual CategoryPtr extractCategoryBSIFT(const CategoryPtr category) {
            std::vector<ImagePtr> bsiftImages(category->getImages().size());

            for (auto& img : category->getImages()) {
                bsiftImages.push_back(extractImageBSIFT(img));
            }

            return std::make_shared<Category>(category->getName(), category->getPath(), std::move(bsiftImages));
        }

        virtual DatabasePtr extractDatabaseBSIFT(const DatabasePtr database) {
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

        virtual DatabaseTranslatorPtr getDatabaseTranslatorPtr() const = 0;
    };

}


#endif //FEITIR_BSIFTEXTRACTOR_H
