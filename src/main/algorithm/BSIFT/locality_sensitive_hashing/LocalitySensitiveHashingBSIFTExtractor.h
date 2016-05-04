//
// Created by Przemek Piórkowski on 03.05.2016.
//

#ifndef FEITIR_LOCALITYSENSITIVEHASHING_H
#define FEITIR_LOCALITYSENSITIVEHASHING_H

#include <iostream>
#include <functional>
#include <eigen3/Eigen/Dense>
#include <opencv2/core/eigen.hpp>
#include "src/main/algorithm/BSIFT/BSIFTExtractor.h"
#include "src/main/util/eigenmvn.h"


namespace feitir {

    template <std::size_t N>
    class LocalitySensitiveHashingBSIFTExtractor : public BSIFTExtractor<N> {

    public:

        LocalitySensitiveHashingBSIFTExtractor(std::vector<std::function<std::vector<bool>(cv::Mat row)>> hashFunctions)
                : hashFunctions{std::move(hashFunctions)} { }

        virtual typename BSIFTExtractor<N>::DatabaseTranslatorPtr getDatabaseTranslatorPtr() const override {
            return std::make_shared<const BSIFTDatabaseTranslator<N>>();
        }

        static std::vector<std::function<std::vector<bool>(cv::Mat row)>> generateRandomHashFunctions() {
            std::vector<std::function<std::vector<bool>(cv::Mat row)>> hashFunctions;
            Eigen::VectorXd mean = Eigen::VectorXd::Zero(N);
            Eigen::MatrixXd cov= Eigen::MatrixXd::Identity(N, N);
            Eigen::EigenMultivariateNormal<double> normalGenerator(mean, cov);

            cv::Mat samples;
            cv::eigen2cv(normalGenerator.samples(N), samples);
            samples.convertTo(samples, CV_32F);

            auto hashFunction = [] (cv::Mat row, cv::Mat hashVector) {
                assert (row.rows == 1 && hashVector.cols == 1);
                std::vector<bool> hashResult;
                cv::Mat multiplicationResult = row * hashVector;
                hashResult.push_back(multiplicationResult.at<float>(0,0) > 0);
                return hashResult;
            };

            for (unsigned i = 0; i < samples.cols; ++i) {
                hashFunctions.push_back(std::bind(hashFunction, std::placeholders::_1, samples.col(i)));
            }

            return hashFunctions;
        }

    protected:
        virtual typename BSIFTExtractor<N>::BSIFT processRow(cv::Mat row) override {
            assert(row.rows == 1);
            typename BSIFTExtractor<N>::BSIFT result;
            unsigned resultPosition = 0;

            for (const auto& fun : hashFunctions) {
                std::vector<bool> hashResult = fun(row);
                for (unsigned i = 0; i < hashResult.size(); ++i) {
                    assert (resultPosition < N);
                    result[resultPosition++] = hashResult[i];
                }
            }

            assert (resultPosition == N);

            return result;
        }

    private:
        std::vector<std::function<std::vector<bool>(cv::Mat row)>> hashFunctions;
    };
}


#endif //FEITIR_LOCALITYSENSITIVEHASHING_H
