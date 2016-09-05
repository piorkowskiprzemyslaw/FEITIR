//
// Created by Przemek Piórkowski on 05.09.2016.
//

#include "DatabaseTranslatorPreserveOriginal.h"

namespace feitir {

    ImagePtr DatabaseTranslatorPreserveOriginal::transformImage(const VocabularyTypePtr vocabulary,
                                                                const ImagePtr image) const {
        return imageFactory.createImage(image, image->getDescriptors(),
                                        std::move(vocabulary->getNearestVisualWords(image->getDescriptors())));
    }

}
