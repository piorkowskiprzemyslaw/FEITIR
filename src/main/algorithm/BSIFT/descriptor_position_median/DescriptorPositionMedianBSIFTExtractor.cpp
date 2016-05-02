//
// Created by Przemek Piórkowski on 02.05.2016.
//

#include "DescriptorPositionMedianBSIFTExtractor.h"

namespace feitir {

    DescriptorPositionMedianBSIFTExtractor::BSIFT DescriptorPositionMedianBSIFTExtractor::processRow(cv::Mat row) {
        if (medianValues.empty()) {
            throw std::logic_error("median values array is empty\n"
                                           "call DescriptorPositionMedianBSIFTExtractor::extractDatabaseBSIFT");
        }
        assert(row.rows == 1);
        assert(row.cols == medianValues.size());

        BSIFT descriptor;
        for (int i = 0; i < row.cols; ++i) {
            descriptor[i] = (row.at<float>(0,i) > medianValues[i]);
        }
        return descriptor;
    }

    void DescriptorPositionMedianBSIFTExtractor::computeMedianValues(const DatabasePtr database) {
        cv::Mat data;
        for (auto img : *database) {
            data.push_back(img->getDescriptors());
        }

        medianValues.clear();
        for (unsigned i = 0; i < data.cols; ++i) {
            std::vector<float> column;
            data.col(i).copyTo(column);
            medianValues.push_back(util.median(column));
        }
    }

    DatabasePtr DescriptorPositionMedianBSIFTExtractor::extractDatabaseBSIFT(const DatabasePtr database) {
        computeMedianValues(database);
        return BSIFTExtractor<128>::extractDatabaseBSIFT(database);
    }

    DescriptorPositionMedianBSIFTExtractor::DatabaseTranslatorPtr DescriptorPositionMedianBSIFTExtractor::getDatabaseTranslatorPtr() const {
        return std::make_shared<const BSIFTDatabaseTranslator<128>>();
    }
}