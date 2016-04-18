//
// Created by Przemek Piórkowski on 04.04.2016.
//

#include "KMeansConfig.h"

namespace feitir {

    KMeansParameter::KMeansParameter(cv::Mat data, const int K) : data{data}, K{K} {

    }

    cv::Mat KMeansParameter::getData() const {
        return data;
    }

    const int KMeansParameter::getK() const {
        return K;
    }

    KMeansParameter::KMeansParameter(const DatabasePtr database, const int K) : K{K} {
        for (auto img : *database) {
            data.push_back(img->getDescriptors());
        }
    }


    KMeansVocabularyType::KMeansVocabularyType(cv::Mat vocabularyMatrix) : vocabularyMatrix{vocabularyMatrix} { }

    cv::Mat KMeansVocabularyType::getVocabularyMatrix() const {
        return vocabularyMatrix;
    }
}