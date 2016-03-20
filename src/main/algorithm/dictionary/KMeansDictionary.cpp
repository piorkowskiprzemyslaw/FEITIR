//
// Created by Przemek Piórkowski on 19.03.2016.
//

#include "KMeansDictionary.h"

namespace feitir {

    cv::Mat KMeansDictionary::create(cv::InputArray data, int K) const {
        cv::Mat labels, centers;
        //TODO think about better adjustment of this parameters.
        cv::kmeans(data, K, labels, cv::TermCriteria(cv::TermCriteria::EPS, 10, 1.0), 10, cv::KMEANS_PP_CENTERS, centers);
        return centers;
    }
}