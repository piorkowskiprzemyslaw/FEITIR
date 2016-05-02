//
// Created by Przemek Piórkowski on 02.05.2016.
//

#ifndef FEITIR_DESCRIPTORPOSITIONMEDIANBSIFTEXTRACTOR_H
#define FEITIR_DESCRIPTORPOSITIONMEDIANBSIFTEXTRACTOR_H

#include "src/main/util/Util.h"
#include "src/main/algorithm/BSIFT/BSIFTExtractor.h"
#include "src/main/algorithm/BSIFT/BSIFTDatabaseTranslator.h"

namespace feitir {

    class DescriptorPositionMedianBSIFTExtractor : public BSIFTExtractor<128> {
    private:
        Util util;
        std::vector<float> medianValues;

    protected:
        virtual BSIFT processRow(cv::Mat row) override;
        void computeMedianValues(const DatabasePtr database);

    public:
        virtual DatabasePtr extractDatabaseBSIFT(const DatabasePtr database) override;
        virtual DatabaseTranslatorPtr getDatabaseTranslatorPtr() const override;
    };

}


#endif //FEITIR_DESCRIPTORPOSITIONMEDIANBSIFTEXTRACTOR_H
