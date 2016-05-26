//
// Created by Przemek Piórkowski on 03.05.2016.
//

#ifndef FEITIR_LOCALITYSENSITIVEHASHING_H
#define FEITIR_LOCALITYSENSITIVEHASHING_H

#include <iostream>
#include <functional>
#include <eigen3/Eigen/Dense>
#include <opencv2/core/eigen.hpp>
#include "src/main/algorithm/BSIFT/BSIFTExtractor.h"
#include "src/main/util/eigenmvn.h"


namespace feitir {

    class LocalitySensitiveHashingBSIFTExtractor : public BSIFTExtractor {
    public:

        LocalitySensitiveHashingBSIFTExtractor(const unsigned N,
                                               std::vector<std::function<std::vector<bool>(cv::Mat row)>> hashFunctions)
                : BSIFTExtractor{N}, hashFunctions{std::move(hashFunctions)} { }

        static std::vector<std::function<std::vector<bool>(cv::Mat row)>> generateRandomHashFunctions(const unsigned N);

    protected:
        virtual BSIFT processRow(cv::Mat row);

    private:
        std::vector<std::function<std::vector<bool>(cv::Mat row)>> hashFunctions;
    };
}


#endif //FEITIR_LOCALITYSENSITIVEHASHING_H
