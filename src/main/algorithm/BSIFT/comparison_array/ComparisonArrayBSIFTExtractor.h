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

    template <std::size_t N, typename Fi = decltype(GREATERWINS)>
    class ComparisonArrayBSIFTExtractor : public BSIFTExtractor<N> {
    public:

        ComparisonArrayBSIFTExtractor(const unsigned L, const unsigned T, Fi fi = GREATERWINS)
                : L{L}, T{T}, fiFunction{fi} { }

        virtual typename BSIFTExtractor<N>::DatabaseTranslatorPtr getDatabaseTranslatorPtr() const override {
            return std::make_shared<const BSIFTDatabaseTranslator<N>>();
        }

    protected:
        const std::pair<bool, bool> C1 = {true, true};
        const std::pair<bool, bool> C2 = {true, false};
        const std::pair<bool, bool> C3 = {false, false};

        virtual typename BSIFTExtractor<N>::BSIFT processRow(cv::Mat row) override {
            assert (row.rows == 1);
            std::vector<bool> comparasionString;

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

                    comparasionString.push_back(resultBoolPair.first);
                    comparasionString.push_back(resultBoolPair.second);
                }
            }

            typename BSIFTExtractor<N>::BSIFT result;
            unsigned resultPosition = 0;
            unsigned partSize = comparasionString.size() / L;
            unsigned rest = comparasionString.size() % L;
            unsigned counter = 0;
            std::vector<bool> partialResult;

            for (unsigned i = 0; i < L; ++i) {
                auto beginIt = comparasionString.begin() + counter;
                auto endIt = comparasionString.end();
                if (i < rest) {
                    endIt = comparasionString.begin() + counter + partSize + 1;
                    counter = counter + partSize + 1;
                } else {
                    endIt = comparasionString.begin() + counter + partSize;
                    counter = counter + partSize;
                }
                partialResult = fiFunction(std::vector<bool>(beginIt, endIt));

                for (int j = 0; j < partialResult.size(); ++j) {
                    assert (resultPosition < N);
                    result[resultPosition++] = partialResult[j];
                }
            }

            assert (resultPosition == N);

            return result;
        }

    private:
        const unsigned L;
        const unsigned T;
        const Fi fiFunction;
    };

}


#endif //FEITIR_COMPARISONARRAYBSIFTEXTRACTOR_H