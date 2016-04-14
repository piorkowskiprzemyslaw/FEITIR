//
// Created by Przemek Piórkowski on 13.04.2016.
//

#include "BIFConfig.h"

namespace feitir {

    BIFParameters::BIFParameters(const DatabasePtr database,
                                 const VocabularyTypePtr vocabulary,
                                 const std::size_t treshold) : database{database},
                                                               vocabulary{vocabulary},
                                                               treshold{treshold} { }

    const DatabasePtr BIFParameters::getDatabase() const {
        return database;
    }

    const VocabularyTypePtr BIFParameters::getVocabulary() const {
        return vocabulary;
    }

    const size_t BIFParameters::getTreshold() const {
        return treshold;
    }
}

