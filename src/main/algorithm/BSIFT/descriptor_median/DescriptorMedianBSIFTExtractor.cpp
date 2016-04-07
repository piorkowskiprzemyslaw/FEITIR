//
// Created by Przemek Piórkowski on 28.03.2016.
//

#include "DescriptorMedianBSIFTExtractor.h"

namespace feitir {

    DescriptorMedianBSIFTExtractor::ImageBSIFTPtr DescriptorMedianBSIFTExtractor::extractImageBSIFT(const ImagePtr image) {
        std::vector<BSIFT> descriptors(image->getDescriptors().rows);

        for (int i = 0; i < image->getDescriptors().rows ; ++i) {
            descriptors[i] = processRow(image->getDescriptors().row(i));
        }

        return std::make_shared<ImageBSIFT>(image, std::move(descriptors));
    }

    DescriptorMedianBSIFTExtractor::BSIFT DescriptorMedianBSIFTExtractor::processRow(cv::Mat row) {
        assert(row.cols == 128);
        std::vector<float> elements(row.cols);
        for (int i = 0; i < row.cols; ++i) {
            elements[i] = row.at<float>(0, i);
        }
        float medianValue = util.median<float, float>(elements);

        BSIFT descriptor;
        for (int i = 0; i < row.cols; ++i) {
            descriptor[i] = (row.at<float>(0,i) > medianValue);
        }
        return descriptor;
    }

    DescriptorMedianBSIFTExtractor::DatabaseTranslatorPtr DescriptorMedianBSIFTExtractor::getDatabaseTranslatorPtr() const {
        return std::make_shared<BSIFTDatabaseTranslator<128>>();
    }
}