//
// Created by Przemek Piórkowski on 15.04.2016.
//

#include "SWIFConfig.h"

namespace feitir {

    SWIFParameters::SWIFParameters(DatabasePtr database, VocabularyTypePtr vocabulary, const MatchingFunc &matchingFunc,
                                   int p, int K, int distanceTreshold)
            : p{p}, distanceTreshold{distanceTreshold}, K{K}, transformedDb{database},
              vocabulary{vocabulary}, matchingFunc{matchingFunc} { }

    int SWIFParameters::getP() const {
        return p;
    }

    int SWIFParameters::getDistanceTreshold() const {
        return distanceTreshold;
    }

    const DatabasePtr SWIFParameters::getTransformedDb() const {
        return transformedDb;
    }

    const VocabularyTypePtr SWIFParameters::getVocabulary() const {
        return vocabulary;
    }

    int SWIFParameters::getK() const {
        return K;
    }

    const MatchingFunc& SWIFParameters::getMatchingFunc() const {
        return matchingFunc;
    }
}