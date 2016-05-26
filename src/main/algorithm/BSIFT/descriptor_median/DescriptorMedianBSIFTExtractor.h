//
// Created by Przemek Piórkowski on 28.03.2016.
//

#ifndef FEITIR_DESCRIPTORMEDIANBSIFTEXTRACTOR_H
#define FEITIR_DESCRIPTORMEDIANBSIFTEXTRACTOR_H

#include <opencv2/core/mat.hpp>
#include "src/main/util/Util.h"
#include "src/main/algorithm/BSIFT/BSIFTExtractor.h"
#include "src/main/algorithm/BSIFT/BSIFTDatabaseTranslator.h"

namespace feitir {

    class DescriptorMedianBSIFTExtractor : public BSIFTExtractor {
    private:
        Util util;
    protected:
        virtual BSIFT processRow(cv::Mat row) override;
    public:
        DescriptorMedianBSIFTExtractor() : BSIFTExtractor{128} { }
    };

}


#endif //FEITIR_DESCRIPTORMEDIANBSIFTEXTRACTOR_H
