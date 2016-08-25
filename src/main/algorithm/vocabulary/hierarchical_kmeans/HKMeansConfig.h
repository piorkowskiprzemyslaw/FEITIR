//
// Created by Przemek Piórkowski on 18.04.2016.
//

#ifndef FEITIR_HKMEANSCONFIG_H
#define FEITIR_HKMEANSCONFIG_H

#include <opencv2/opencv.hpp>
#include "src/main/database/Database.h"
#include "src/main/algorithm/vocabulary/VocabularyConfig.h"

namespace feitir {

    class HKMeansParameter {
    private:
        // matrix with whole data
        cv::Mat data;
        // number of words at each vocabulary node
        const unsigned K;
        // height of created vocabulary tree
        const unsigned L;

    public:
        HKMeansParameter(cv::Mat data, const unsigned K, const unsigned L);

        HKMeansParameter(const DatabasePtr database, const unsigned K, const unsigned L);

        const cv::Mat getData() const;

        const unsigned getK() const;

        const unsigned int getL() const;
    };

    class HKMeansNode;
    using HKMeansNodePtr = std::shared_ptr<HKMeansNode>;
    using HKMeansNodeWeakPtr = std::weak_ptr<HKMeansNode>;

    class HKMeansNode {
    public:
        HKMeansNode(const cv::Mat nodeWords, const HKMeansNodeWeakPtr parent);
        const cv::Mat getNodeWords() const;
        void addChildren(HKMeansNodePtr child);
        const std::vector<HKMeansNodePtr> & getChildrens() const;
        const HKMeansNodeWeakPtr getParent() const;
        bool operator==(const HKMeansNode& rhs) const;
        inline bool operator!=(const HKMeansNode& rhs) const {
            return !(*this == rhs);
        }
        int getOffset() const;
        void setOffset(int offset);

    private:
        cv::Mat nodeWords;
        std::vector<HKMeansNodePtr> childrens;
        HKMeansNodeWeakPtr parent;
        int offset;
    };

    class HKMeansVocabularyType : public VocabularyType {
    public:
        HKMeansVocabularyType(HKMeansNodePtr root, unsigned K, unsigned L);
        virtual cv::Mat getVocabularyMatrix() const;
        virtual std::vector<cv::DMatch> getNearestVisualWords(cv::Mat queryFeatures);
        const HKMeansNodePtr getRoot() const;
        unsigned int getK() const;
        unsigned int getL() const;
        bool operator==(const HKMeansVocabularyType& rhs) const;
        inline bool operator!=(const HKMeansVocabularyType& rhs) const {
            return !(*this == rhs);
        }

    protected:
        cv::Mat getVocabulary(HKMeansNodePtr root);
        std::vector<cv::DMatch> getNearestVisualWordsConcurrent(cv::Mat queryFeatures,
                                                                unsigned numberOfThreads);
        cv::DMatch getNearestVisualWord(HKMeansNodePtr root, cv::Mat queryFeature);
        void initializeNode(HKMeansNodePtr node);
        int computeVisualWordOffset(HKMeansNodePtr leaf);

    private:
        cv::BFMatcher matcher;
        unsigned K;
        unsigned L;
        cv::Mat vocabularyMatrix;
        HKMeansNodePtr root;

    };

    using HKMeansParameterPtr = std::shared_ptr<HKMeansParameter>;
    using HKMeansVocabularyTypePtr = std::shared_ptr<HKMeansVocabularyType>;
}


#endif //FEITIR_HKMEANSCONFIG_H
