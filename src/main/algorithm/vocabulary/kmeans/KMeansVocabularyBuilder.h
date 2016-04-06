//
// Created by Przemek Piórkowski on 19.03.2016.
//

#ifndef FEITIR_KMEANSDICTIONARY_H
#define FEITIR_KMEANSDICTIONARY_H

#include <opencv2/core.hpp>
#include <boost/filesystem.hpp>
#include "src/main/algorithm/vocabulary/kmeans/KMeansConfig.h"
#include "src/main/algorithm/vocabulary/VocabularyBuilder.h"

namespace feitir {

    /**
     * KMeansVocabularyBuilder is implementation of kmeans algorithm for vocabulary building.
     */
    class KMeansVocabularyBuilder : public VocabularyBuilder<KMeansParameterPtr, KMeansVocabularyTypePtr> {
    public:
        static const std::string VOCABULARY_FILE_NODE;

        explicit KMeansVocabularyBuilder();

        virtual ~KMeansVocabularyBuilder();

        virtual KMeansVocabularyTypePtr build(KMeansParameterPtr parameter);

        virtual void saveToFile(KMeansVocabularyTypePtr vocabulary, const std::string &file) const;

        virtual KMeansVocabularyTypePtr readFromFile(const std::string &file) const;

    };

}


#endif //FEITIR_KMEANSDICTIONARY_H
