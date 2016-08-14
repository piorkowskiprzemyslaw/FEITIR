//
// Created by Przemek Piórkowski on 29.04.2016.
//

#ifndef FEITIR_COMPARISONARRAYBSIFTEXTRACTOR_H
#define FEITIR_COMPARISONARRAYBSIFTEXTRACTOR_H

#include <iostream>
#include <algorithm>
#include "src/main/algorithm/BSIFT/BSIFTExtractor.h"
#include "src/main/algorithm/BSIFT/BSIFTDatabaseTranslator.h"

namespace feitir {

    static const auto GREATERWINS = [] (std::vector<bool> inputVector) {
        std::vector<bool> result;
        auto trueCount = std::count(inputVector.begin(), inputVector.end(), true);
        result.push_back(trueCount > (inputVector.size() / 2));
        return result;
    };

    template <typename Fi = decltype(GREATERWINS)>
    class ComparisonArrayBSIFTExtractor : public BSIFTExtractor {
    public:

        ComparisonArrayBSIFTExtractor(const unsigned N, const int L, const int T, Fi fi = GREATERWINS)
                : BSIFTExtractor{N}, L{L}, T{T}, fiFunction{fi} { }

    protected:
        const std::pair<bool, bool> C1 = {true, true};
        const std::pair<bool, bool> C2 = {true, false};
        const std::pair<bool, bool> C3 = {false, false};

        virtual BSIFTExtractor::BSIFT processRow(cv::Mat row) override {
            assert (row.rows == 1);
            std::vector<bool> comparisonString;

            for (unsigned i = 0; i < row.cols; ++i) {
                for (unsigned j = i + 1; j < row.cols; ++j) {
                    int comparasionResult = row.at<float>(0, j) - row.at<float>(0, i);
                    std::pair<bool, bool> resultBoolPair;

                    if (comparasionResult > T) {
                        resultBoolPair = C1;
                    } else if (abs(comparasionResult) <= T) {
                        resultBoolPair = C2;
                    } else {
                        resultBoolPair = C3;
                    }

                    comparisonString.push_back(resultBoolPair.first);
                    comparisonString.push_back(resultBoolPair.second);
                }
            }

            typename BSIFTExtractor::BSIFT result(getN());
            unsigned resultPosition = 0;
            unsigned long partSize = comparisonString.size() / L;
            unsigned long rest = comparisonString.size() % L;
            unsigned long counter = 0;
            std::vector<bool> partialResult;

            for (unsigned i = 0; i < L; ++i) {
                auto beginIt = comparisonString.begin() + counter;
                decltype(beginIt) endIt;
                if (i < rest) {
                    endIt = comparisonString.begin() + counter + partSize + 1;
                    counter = counter + partSize + 1;
                } else {
                    endIt = comparisonString.begin() + counter + partSize;
                    counter = counter + partSize;
                }
                partialResult = fiFunction(std::vector<bool>(beginIt, endIt));

                for (int j = 0; j < partialResult.size(); ++j) {
                    assert (resultPosition < getN());
                    result[resultPosition++] = partialResult[j];
                }
            }

            assert (resultPosition == getN());
            return result;
        }

    private:
        const int L;
        const int T;
        const Fi fiFunction;
    };

}


#endif //FEITIR_COMPARISONARRAYBSIFTEXTRACTOR_H
