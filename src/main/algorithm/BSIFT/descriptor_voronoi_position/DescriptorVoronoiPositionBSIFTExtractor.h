//
// Created by Przemek Piórkowski on 16.05.2016.
//

#ifndef FEITIR_DESCRIPTORVORONOIPOSITION_H
#define FEITIR_DESCRIPTORVORONOIPOSITION_H

#include <iostream>
#include <random>
#include <eigen3/Eigen/Dense>
#include <opencv2/core/eigen.hpp>
#include "src/main/database/Database.h"
#include "src/main/algorithm/vocabulary/VocabularyConfig.h"
#include "src/main/algorithm/BSIFT/BSIFTExtractor.h"

namespace feitir {

    template <std::size_t N>
    class DescriptorVoronoiPositionBSIFTExtractor : public BSIFTExtractor<N> {
    public:
        DescriptorVoronoiPositionBSIFTExtractor(const VocabularyTypePtr vocabulary, DatabasePtr database)
                : vocabulary{vocabulary},
                  databaseWeakPtr{database},
                  medians{std::vector<std::array<float, N>>(vocabularySize())} {
            generateP();
            computeMedians();
        }

        virtual typename BSIFTExtractor<N>::DatabaseTranslatorPtr getDatabaseTranslatorPtr() const override {
            return std::make_shared<const BSIFTDatabaseTranslator<N>>();
        }

    protected:
        virtual typename BSIFTExtractor<N>::BSIFT processRow(cv::Mat row) override {
            typename BSIFTExtractor<N>::BSIFT result;
            std::vector<cv::DMatch> matches = vocabulary->getNearestVisualWords(row);
            std::array<float, N> medianValues = medians[matches[0].trainIdx];
            cv::Mat z = P * row.t();
            for (int i = 0 ; i < N ; ++i) {
                result[i] = z.at<float>(i, 0) > medianValues[i];
            }
            return result;
        }

        inline int vocabularySize() const { return vocabulary->getVocabularyMatrix().rows;}

        void generateP() {
            using namespace std;
            using namespace Eigen;
            default_random_engine generator;
            normal_distribution<float> distribution(0, 1);
            auto gauss = [&] (int) {return distribution(generator);};
            auto descriptorSize = vocabulary->getVocabularyMatrix().cols;
            MatrixXf randomMatrix = MatrixXf::NullaryExpr(descriptorSize, descriptorSize, gauss);
            MatrixXf result(MatrixXf::Identity(N, descriptorSize));
            HouseholderQR<MatrixXf> qr(randomMatrix);
            result = result * qr.householderQ();
            cv::eigen2cv(result, P);
        }

        void computeMedians() {
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
                    std::array<float, N> centroidMedians;
                    // for each column in this matrix compute median value and
                    // update corresponding centroidMedians value
                    for (int j = 0; j < centroidMap.cols; ++j) {
                        std::vector<float> column;
                        centroidMap.col(j).copyTo(column);
                        centroidMedians[j] = util.median(column);
                    }
                    medians[i] = centroidMedians;
                }
            } else {
                throw std::runtime_error("cannot aquire database pointer");
            }
        }

    private:
        VocabularyTypePtr vocabulary;
        std::weak_ptr<Database> databaseWeakPtr;
        cv::Mat P;
        std::vector<std::array<float, N>> medians;
        Util util;
    };
}

#endif //FEITIR_DESCRIPTORVORONOIPOSITION_H
