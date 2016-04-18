//
// Created by Przemek Piórkowski on 15.04.2016.
//

#include "SWIFConfig.h"

namespace feitir {

    SWIFParameters::SWIFParameters(size_t p, size_t distanceTreshold, size_t K,
                                   DatabasePtr database, VocabularyTypePtr vocabulary)
            : p{p}, distanceTreshold{distanceTreshold}, K{K},
              transformedDb{database}, vocabulary{vocabulary} { }

    size_t SWIFParameters::getP() const {
        return p;
    }

    size_t SWIFParameters::getDistanceTreshold() const {
        return distanceTreshold;
    }

    const DatabasePtr SWIFParameters::getTransformedDb() const {
        return transformedDb;
    }

    const VocabularyTypePtr SWIFParameters::getVocabulary() const {
        return vocabulary;
    }

    size_t SWIFParameters::getK() const {
        return K;
    }
}