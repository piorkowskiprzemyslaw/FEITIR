//
// Created by Przemek Piórkowski on 19.03.2016.
//

#ifndef FEITIR_KMEANSDICTIONARY_H
#define FEITIR_KMEANSDICTIONARY_H

#include <opencv2/core.hpp>

namespace feitir {

    class KMeansDictionary {
    public:
        cv::Mat create(cv::InputArray data, int K) const;
    };

}


#endif //FEITIR_KMEANSDICTIONARY_H
