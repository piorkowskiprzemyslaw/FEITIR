//
// Created by Przemek Piórkowski on 07.04.2016.
//

#ifndef FEITIR_BSIFTDATABASETRANSLATOR_H
#define FEITIR_BSIFTDATABASETRANSLATOR_H

#include <iostream>
#include "src/main/algorithm/BSIFT/ImageBSIFT.h"
#include "src/main/algorithm/vocabulary/DatabaseTranslator.h"

namespace feitir {

    /**
     * BSIFT database translator should be used *after* extracting BSIFT informations from whole database
     * it persists BSIFT descriptor while dropping out original descriptor value.
     */
    class BSIFTDatabaseTranslator : public DatabaseTranslator {
    public:
        virtual ImagePtr transformImage(const VocabularyTypePtr vocabulary, const ImagePtr image) const {
            std::vector<cv::DMatch> matches = vocabulary->getNearestVisualWords(image->getDescriptors());

            ImageBSIFTPtr bsiftPtr = std::dynamic_pointer_cast<ImageBSIFT>(image);
            if (bsiftPtr != nullptr) {
                return std::make_shared<ImageBSIFT>(bsiftPtr, std::move(matches));
            }

            return imageFactory.createImage(image, std::move(matches));
        }
    };

    using BSIFTDatabaseTranslatorPtr = std::shared_ptr<const BSIFTDatabaseTranslator>;

}


#endif //FEITIR_BSIFTDATABASETRANSLATOR_H
