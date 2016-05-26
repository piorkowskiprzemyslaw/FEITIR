//
// Created by przemek on 26.05.16.
//

#include "LocalitySensitiveHashingBSIFTExtractor.h"

namespace feitir {

    std::vector<std::function<std::vector<bool>(cv::Mat row)>>
    LocalitySensitiveHashingBSIFTExtractor::generateRandomHashFunctions(const unsigned N) {
        std::vector<std::function<std::vector<bool>(cv::Mat row)>> hashFunctions;
        Eigen::VectorXd mean = Eigen::VectorXd::Zero(N);
        Eigen::MatrixXd cov = Eigen::MatrixXd::Identity(N, N);
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

    LocalitySensitiveHashingBSIFTExtractor::BSIFT LocalitySensitiveHashingBSIFTExtractor::processRow(cv::Mat row) {
        assert(row.rows == 1);
        BSIFT result(getN());
        unsigned resultPosition = 0;

        for (const auto& fun : hashFunctions) {
            std::vector<bool> hashResult = fun(row);
            for (unsigned i = 0; i < hashResult.size(); ++i) {
                assert (resultPosition < getN());
                result[resultPosition++] = hashResult[i];
            }
        }

        assert (resultPosition == getN());

        return result;
    }
}