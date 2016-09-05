//
// Created by Przemek Piórkowski on 05.09.2016.
//

#ifndef FEITIR_DATABASETRANSLATORPRESERVEORIGINAL_H
#define FEITIR_DATABASETRANSLATORPRESERVEORIGINAL_H

#include "DatabaseTranslator.h"

namespace feitir {

    class DatabaseTranslatorPreserveOriginal : public DatabaseTranslator {

    public:
        virtual ImagePtr transformImage(const VocabularyTypePtr vocabulary, const ImagePtr image) const override;
    };

}


#endif //FEITIR_DATABASETRANSLATORPRESERVEORIGINAL_H
