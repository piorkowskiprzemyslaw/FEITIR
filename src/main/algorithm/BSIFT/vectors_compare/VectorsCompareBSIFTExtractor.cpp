//
// Created by Przemek Piórkowski on 09.05.2016.
//

#include "VectorsCompareBSIFTExtractor.h"

namespace feitir {

    VectorsCompareBSIFTExtractor::DatabaseTranslatorPtr VectorsCompareBSIFTExtractor::getDatabaseTranslatorPtr() const {
        return std::make_shared<const BSIFTDatabaseTranslator<384>>();
    }

    VectorsCompareBSIFTExtractor::BSIFT VectorsCompareBSIFTExtractor::processRow(cv::Mat row) {
        BSIFT result;
        int resultFirstIdx = 0;
        for (int i = 0; i < BINS_NUMBER; ++i) {
            for (int j = 0; j < BINS_NUMBER; ++j, resultFirstIdx += (3 * VECTORS_PER_BIN)) {
                auto currentOriHist = oriHist(i, j, row);
                auto horizontalNbr = j == BINS_NUMBER - 1 ? oriHist(i, 0, row) : oriHist(i, j + 1, row);
                auto verticalNbr = i == BINS_NUMBER - 1 ? oriHist(0, i, row) : oriHist(i + 1, j, row);
                innerValue(result, resultFirstIdx, currentOriHist);
                nbrCmp(result, resultFirstIdx + VECTORS_PER_BIN, currentOriHist, horizontalNbr);
                nbrCmp(result, resultFirstIdx + VECTORS_PER_BIN * 2, currentOriHist, verticalNbr);
            }
        }
        return result;
    }


    void VectorsCompareBSIFTExtractor::innerValue(VectorsCompareBSIFTExtractor::BSIFT &result, int startIdx,
                                                  cv::Mat oriHist) {
        for (int i = 0; i < oriHist.cols; ++i) {
            result[startIdx + i] = oriHist.at<float>(i) >= oriHist.at<float>(i == oriHist.cols - 1 ? 0 : i + 1);
        }
    }

    void VectorsCompareBSIFTExtractor::nbrCmp(BSIFT &result, int startIdx, cv::Mat oriHist, cv::Mat nbr) {
        assert (oriHist.cols == nbr.cols);
        for (int i = 0; i < oriHist.cols; ++i) {
            result[startIdx + i] = oriHist.at<float>(i) >= nbr.at<float>(i);
        }
    }
}