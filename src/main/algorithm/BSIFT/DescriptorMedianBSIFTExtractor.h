//
// Created by Przemek Piórkowski on 28.03.2016.
//

#ifndef FEITIR_DESCRIPTORMEDIANBSIFTEXTRACTOR_H
#define FEITIR_DESCRIPTORMEDIANBSIFTEXTRACTOR_H

#include <iostream>
#include <algorithm>
#include <boost/accumulators/accumulators.hpp>
#include <boost/accumulators/statistics/stats.hpp>
#include <boost/accumulators/statistics/median.hpp>
#include <opencv2/core/mat.hpp>
#include "src/main/util/Util.h"
#include "src/main/algorithm/BSIFT/BSIFTExtractor.h"

namespace feitir {

    class DescriptorMedianBSIFTExtractor : public BSIFTExtractor {
    private:
        Util util;
    protected:
        BSIFT processRow(cv::Mat row);
    public:
        virtual ImageBSIFTPtr extractBSIFT(const ImagePtr image);
    };

}


#endif //FEITIR_DESCRIPTORMEDIANBSIFTEXTRACTOR_H
