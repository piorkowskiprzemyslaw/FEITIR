//
// Created by Przemek Piórkowski on 18.04.2016.
//

#include "HKMeansVocabularyBuilder.h"

namespace feitir {

    const std::string HKMeansVocabularyBuilder::VOCABULARY_FILE_K = "parameterK";
    const std::string HKMeansVocabularyBuilder::VOCABULARY_FILE_L = "parameterL";
    const std::string HKMeansVocabularyBuilder::VOCABULARY_FILE_NODE_NAME = "vocabularyNode";

    HKMeansVocabularyTypePtr HKMeansVocabularyBuilder::build(HKMeansParameterPtr parameter) {
        return std::make_shared<HKMeansVocabularyType>(buildVocabularyNode(parameter->getData(),
                                                                           std::weak_ptr<HKMeansNode>(),
                                                                           parameter->getK(),
                                                                           parameter->getL()),
                                                       parameter->getK(),
                                                       parameter->getL());
    }

    void HKMeansVocabularyBuilder::saveToFile(HKMeansVocabularyTypePtr vocabulary, const std::string &file) const {
        if (!boost::filesystem::exists(file)) {
            cv::FileStorage fs(file.c_str(), cv::FileStorage::WRITE);
            cv::write(fs, VOCABULARY_FILE_K, static_cast<int>(vocabulary->getK()));
            cv::write(fs, VOCABULARY_FILE_L, static_cast<int>(vocabulary->getL()));
            int lastNode = saveVocabularyNodeToFile(vocabulary->getRoot(), fs, 1);
            std::cout << lastNode << std::endl;
            fs.release();
        }
    }

    int HKMeansVocabularyBuilder::saveVocabularyNodeToFile(HKMeansNodePtr root, cv::FileStorage &fs,
                                                           int nodeNumber) const {
        cv::write(fs, VOCABULARY_FILE_NODE_NAME + std::to_string(nodeNumber++), root->getNodeWords());
        for (auto child : root->getChildrens()) {
            nodeNumber = saveVocabularyNodeToFile(child, fs, nodeNumber);
        }
        return nodeNumber;
    }

    HKMeansVocabularyTypePtr HKMeansVocabularyBuilder::readFromFile(const std::string &file) const {
        return std::make_shared<HKMeansVocabularyType>(nullptr, 0, 0);
    }

    HKMeansNodePtr HKMeansVocabularyBuilder::buildVocabularyNode(cv::Mat data,
                                                                 HKMeansNodeWeakPtr parent,
                                                                 unsigned K, unsigned L) {
        cv::Mat labels, centers;
        cv::kmeans(data, K, labels,
                   cv::TermCriteria(cv::TermCriteria::EPS, 10, 1.0), 10, cv::KMEANS_PP_CENTERS, centers);

        auto node = std::make_shared<HKMeansNode>(centers, parent);

        if (L != 0) {
            std::vector<cv::Mat> childrenData(K);
            for (unsigned i = 0; i < labels.rows; ++i) {
                childrenData[labels.at<int>(i)].push_back(data.row(i));
            }

            std::vector<HKMeansNodePtr> childrens;
            for (unsigned i = 0; i < K; ++i) {
                node->addChildren(buildVocabularyNode(childrenData[i], node, K, L - 1));
            }
        }

        return node;
    }
}