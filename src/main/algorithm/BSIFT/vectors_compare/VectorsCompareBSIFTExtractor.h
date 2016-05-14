//
// Created by Przemek Piórkowski on 09.05.2016.
//

#ifndef FEITIR_VECTORSCOMPAREBSIFTEXTRACTOR_H
#define FEITIR_VECTORSCOMPAREBSIFTEXTRACTOR_H

#include "src/main/algorithm/BSIFT/BSIFTExtractor.h"
#include "src/main/algorithm/BSIFT/BSIFTDatabaseTranslator.h"
#include "opencv2/xfeatures2d/nonfree.hpp"

namespace feitir {

    class VectorsCompareBSIFTExtractor : public BSIFTExtractor<384> {
    public:
        static constexpr int VECTORS_PER_BIN = 8;
        static constexpr int BINS_NUMBER = 4;

        virtual DatabaseTranslatorPtr getDatabaseTranslatorPtr() const;

    protected:
        virtual BSIFT processRow(cv::Mat row);

        void innerValue(BSIFT &result, int startIdx, cv::Mat oriHist);
        void nbrCmp(BSIFT &result, int startIdx, cv::Mat oriHist, cv::Mat nbr);

        inline int beginIdx(int row, int col) { return (BINS_NUMBER*row + col)*VECTORS_PER_BIN;}
        inline int endIdx(int row, int col) { return (BINS_NUMBER*row +(col+1))*VECTORS_PER_BIN;}
        inline cv::Mat oriHist(int row, int col, cv::Mat full) { return full.colRange(beginIdx(row, col), endIdx(row, col));}
    };
}


#endif //FEITIR_VECTORSCOMPAREBSIFTEXTRACTOR_H
