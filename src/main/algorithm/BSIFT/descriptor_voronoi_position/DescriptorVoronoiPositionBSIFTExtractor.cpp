//
// Created by przemek on 25.05.16.
//

#include "DescriptorVoronoiPositionBSIFTExtractor.h"

namespace feitir {

    DescriptorVoronoiPositionBSIFTExtractor::BSIFT DescriptorVoronoiPositionBSIFTExtractor::processRow(cv::Mat row) {
        BSIFT result(getN());
        std::vector<cv::DMatch> matches = vocabulary->getNearestVisualWords(row);
        std::vector<float> medianValues = medians[matches[0].trainIdx];
        cv::Mat z = P * row.t();
        for (int i = 0 ; i < getN() ; ++i) {
            result[i] = z.at<float>(i, 0) > medianValues[i];
        }
        return result;
    }

    void DescriptorVoronoiPositionBSIFTExtractor::generateP() {
        using namespace std;
        using namespace Eigen;
        default_random_engine generator;
        normal_distribution<float> distribution(0, 1);
        auto gauss = [&] (int) {return distribution(generator);};
        auto descriptorSize = vocabulary->getVocabularyMatrix().cols;
        MatrixXf randomMatrix = MatrixXf::NullaryExpr(descriptorSize, descriptorSize, gauss);
        MatrixXf result(MatrixXf::Identity(getN(), descriptorSize));
        HouseholderQR<MatrixXf> qr(randomMatrix);
        result = result * qr.householderQ();
        cv::eigen2cv(result, P);
    }

    void DescriptorVoronoiPositionBSIFTExtractor::computeMedians() {
        if (auto database = databaseWeakPtr.lock()) {
            // matrix of mapped descriptors value per visual word
            std::vector<cv::Mat> mappingResults(vocabularySize());

            // for each image in database extract all its matches
            for (auto img : *database) {
                cv::Mat imgDescriptors = img->getDescriptors();
                std::vector<cv::DMatch> matches = vocabulary->getNearestVisualWords(imgDescriptors);
                // add mapped descriptor value to corresponding to this
                // descriptor visual word mappingResults
                for (auto dmatch : matches) {
                    mappingResults[dmatch.trainIdx].push_back(imgDescriptors.row(dmatch.queryIdx) * P.t());
                }
            }

            // for each visual word get its mapping results matrix
            for (int i = 0; i < mappingResults.size(); ++i) {
                auto centroidMap = mappingResults[i];
                std::vector<float> centroidMedians(getN());
                // for each column in this matrix compute median value and
                // update corresponding centroidMedians value
                for (int j = 0; j < centroidMap.cols; ++j) {
                    std::vector<float> column;
                    centroidMap.col(j).copyTo(column);
                    centroidMedians[j] = Util::median(column);
                }
                medians[i] = centroidMedians;
            }
        } else {
            throw std::runtime_error("cannot acquire database pointer");
        }
    }
}