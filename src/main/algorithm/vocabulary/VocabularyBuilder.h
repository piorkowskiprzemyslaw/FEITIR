//
// Created by Przemek Piórkowski on 04.04.2016.
//

#ifndef FEITIR_VOCABULARY_H
#define FEITIR_VOCABULARY_H

#include <iostream>
#include <vector>
#include "src/main/database/Database.h"
#include "src/main/database/DatabaseFactory.h"
#include "src/main/database/category/Category.h"
#include "src/main/database/category/CategoryFactory.h"
#include "src/main/algorithm/BSIFT/ImageBSIFT.h"

namespace feitir {

    template <class Parameter, class Vocabulary>
    class VocabularyBuilder {
    public:
        virtual ~VocabularyBuilder() { }

        virtual Vocabulary build(Parameter parameter) = 0;

        virtual void saveToFile(Vocabulary vocabulary, const std::string& file) const = 0;

        virtual Vocabulary readFromFile(const std::string& file) const = 0;
    };
}


#endif //FEITIR_VOCABULARY_H
