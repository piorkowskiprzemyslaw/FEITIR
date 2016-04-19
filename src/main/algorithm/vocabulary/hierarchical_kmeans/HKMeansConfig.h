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
        cv::Mat data;
        const unsigned K;
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

    private:
        cv::Mat nodeWords;
        std::vector<HKMeansNodePtr> childrens;
        HKMeansNodeWeakPtr parent;
    };

    class HKMeansVocabularyType : public VocabularyType {
    public:
        HKMeansVocabularyType(HKMeansNodePtr root, unsigned K, unsigned L);
        virtual cv::Mat getVocabularyMatrix() const;
        const HKMeansNodePtr getRoot() const;
        unsigned int getK() const;
        unsigned int getL() const;

    protected:
        cv::Mat getVocabulary(HKMeansNodePtr root);

    private:
        unsigned K;
        unsigned L;
        cv::Mat vocabularyMatrix;
        HKMeansNodePtr root;

    };

    using HKMeansParameterPtr = std::shared_ptr<HKMeansParameter>;
    using HKMeansVocabularyTypePtr = std::shared_ptr<HKMeansVocabularyType>;
}


#endif //FEITIR_HKMEANSCONFIG_H
