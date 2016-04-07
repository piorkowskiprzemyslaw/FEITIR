//
// Created by Przemek Piórkowski on 05.04.2016.
//

#ifndef FEITIR_VOCABULARYCONFIG_H
#define FEITIR_VOCABULARYCONFIG_H


#include <opencv2/core/mat.hpp>

namespace feitir {

    class VocabularyParameter {
    public:

    };

    class VocabularyType {
    public:
        virtual cv::Mat getVocabularyMatrix() const = 0;
    };

    typedef std::shared_ptr<VocabularyParameter> VocabularyParameterPtr;

    typedef std::shared_ptr<VocabularyType> VocabularyTypePtr;
}


#endif //FEITIR_VOCABULARYCONFIG_H