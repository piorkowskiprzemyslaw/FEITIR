//
// Created by Przemek Piórkowski on 07.04.2016.
//

#ifndef FEITIR_DATABASETRANSLATOR_H
#define FEITIR_DATABASETRANSLATOR_H


#include "src/main/database/image/ImageFactory.h"
#include "src/main/database/category/CategoryFactory.h"
#include "src/main/database/DatabaseFactory.h"
#include "VocabularyConfig.h"

namespace feitir {

    class DatabaseTranslator {
    protected:
        const CategoryFactory categoryFactory;
        const DatabaseFactory databaseFactory;
        const ImageFactory imageFactory;
        cv::BFMatcher matcher;

    public:
        DatabaseTranslator();
        virtual ~DatabaseTranslator();
        virtual ImagePtr transformImage(const VocabularyTypePtr vocabulary, const ImagePtr image) const;
        virtual CategoryPtr transformCategory(const VocabularyTypePtr vocabulary, const CategoryPtr category) const;
        virtual DatabasePtr transformDatabase(const VocabularyTypePtr vocabulary, const DatabasePtr database) const;
    };
}


#endif //FEITIR_DATABASETRANSLATOR_H
