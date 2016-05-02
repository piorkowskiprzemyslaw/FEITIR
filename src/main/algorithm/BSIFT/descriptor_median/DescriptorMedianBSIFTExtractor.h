//
// Created by Przemek Piórkowski on 28.03.2016.
//

#ifndef FEITIR_DESCRIPTORMEDIANBSIFTEXTRACTOR_H
#define FEITIR_DESCRIPTORMEDIANBSIFTEXTRACTOR_H

#include <iostream>
#include <opencv2/core/mat.hpp>
#include "src/main/util/Util.h"
#include "src/main/algorithm/BSIFT/BSIFTExtractor.h"
#include "src/main/algorithm/BSIFT/BSIFTDatabaseTranslator.h"

namespace feitir {

    class DescriptorMedianBSIFTExtractor : public BSIFTExtractor<128> {
    private:
        Util util;
    protected:
        virtual BSIFT processRow(cv::Mat row) override;
    public:
        virtual DatabaseTranslatorPtr getDatabaseTranslatorPtr() const override;
    };

}


#endif //FEITIR_DESCRIPTORMEDIANBSIFTEXTRACTOR_H
