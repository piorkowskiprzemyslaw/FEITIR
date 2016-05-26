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
    class BSIFTExtractor {
    public:

        /**
         * Image with Binary SIFT descriptor value.
         */
        using ImageBSIFT = typename feitir::ImageBSIFT;

        /**
         * Binary SIFT descriptor type.
         */
        using BSIFT = typename feitir::ImageBSIFT::BSIFT;

        /**
         * Pointer to image with Binary SIFT descriptor value type.
         */
        using ImageBSIFTPtr = typename feitir::ImageBSIFTPtr;

        /**
         * Pointer to database translator class.
         */
        using DatabaseTranslatorPtr = typename feitir::BSIFTDatabaseTranslatorPtr;

    protected:

        virtual BSIFT processRow(cv::Mat row) = 0;

    public:

        BSIFTExtractor(const unsigned N) : N{N} { }

        virtual ~BSIFTExtractor() { }

        virtual ImageBSIFTPtr extractImageBSIFT(const ImagePtr image);

        virtual CategoryPtr extractCategoryBSIFT(const CategoryPtr category);

        virtual DatabasePtr extractDatabaseBSIFT(const DatabasePtr database);

        virtual DatabaseTranslatorPtr getDatabaseTranslatorPtr() const;

        const unsigned int getN() const;

    private:
        const unsigned N;
    };

    using BSIFTExtractorPtr = std::shared_ptr<BSIFTExtractor>;

}


#endif //FEITIR_BSIFTEXTRACTOR_H
