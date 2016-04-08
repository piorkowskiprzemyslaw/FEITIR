//
// Created by Przemek Piórkowski on 04.04.2016.
//

#ifndef FEITIR_KMEANSCONFIG_H
#define FEITIR_KMEANSCONFIG_H


#include <opencv2/core/mat.hpp>
#include "src/main/database/Database.h"
#include "src/main/algorithm/vocabulary/VocabularyConfig.h"

namespace feitir {

    /**
     * KMeansVocabularyBuilder algorithm parameter.
     */
    class KMeansParameter {
    private:
        cv::Mat data;
        const int K;
    public:
        KMeansParameter(cv::Mat data, const int K);

        KMeansParameter(const DatabasePtr database, const int K);

        cv::Mat getData() const;

        const int getK() const;
    };

    /**
     * Represents vocabulary built by KMeansVocabularyBuilder.
     */
    class KMeansVocabularyType : public VocabularyType {
    private:
        cv::Mat vocabularyMatrix;
    public:
        KMeansVocabularyType(cv::Mat vocabularyMatrix);

        virtual cv::Mat getVocabularyMatrix() const;
    };

    typedef std::shared_ptr<KMeansParameter> KMeansParameterPtr;

    typedef std::shared_ptr<KMeansVocabularyType> KMeansVocabularyTypePtr;

}


#endif //FEITIR_KMEANSCONFIG_H
