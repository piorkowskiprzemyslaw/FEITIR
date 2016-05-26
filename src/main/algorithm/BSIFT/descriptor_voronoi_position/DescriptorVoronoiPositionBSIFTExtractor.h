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

    class DescriptorVoronoiPositionBSIFTExtractor : public BSIFTExtractor {
    public:
        DescriptorVoronoiPositionBSIFTExtractor(const unsigned N, const VocabularyTypePtr vocabulary,
                                                DatabasePtr database) : BSIFTExtractor{N}, vocabulary{vocabulary},
                                                        databaseWeakPtr{database},
                                                        medians{std::vector<std::vector<float>>(vocabularySize())} {
            generateP();
            computeMedians();
        }

    protected:
        virtual BSIFT processRow(cv::Mat row);

        inline int vocabularySize() const { return vocabulary->getVocabularyMatrix().rows;}

        void generateP();

        void computeMedians();

    private:
        VocabularyTypePtr vocabulary;
        std::weak_ptr<Database> databaseWeakPtr;
        cv::Mat P;
        std::vector<std::vector<float>> medians;
        Util util;
    };
}

#endif //FEITIR_DESCRIPTORVORONOIPOSITION_H
