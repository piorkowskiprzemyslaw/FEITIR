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
        cv::Mat vocabulary;
        if (boost::filesystem::exists(file)) {
            cv::FileStorage fs(file.c_str(), cv::FileStorage::READ);
            int K,L;
            cv::read(fs[VOCABULARY_FILE_K], K, -1);
            cv::read(fs[VOCABULARY_FILE_L], L, -1);

            if (K == -1 || L == -1) {
                throw std::invalid_argument("corrupted dictionary file " + file);
            }

            HKMeansNodePtr root;
            int nodeNumber;
            std::tie(nodeNumber, root) = readVocabularyNodeFromFile(fs, K, L, std::weak_ptr<HKMeansNode>(), 1);
            fs.release();
            return std::make_shared<HKMeansVocabularyType>(root, K, L);
        }
        return nullptr;
    }

    std::tuple<int, HKMeansNodePtr> HKMeansVocabularyBuilder::readVocabularyNodeFromFile(cv::FileStorage &fs,
                                                                                        int K, int L,
                                                                                        HKMeansNodeWeakPtr parent,
                                                                                        int nodeNumber) const {
        cv::Mat nodeData;
        cv::read(fs[VOCABULARY_FILE_NODE_NAME + std::to_string(nodeNumber++)], nodeData);

        auto node = std::make_shared<HKMeansNode>(nodeData, parent);
        HKMeansNodePtr child;

        if (L != 0) {
            for (unsigned i = 0; i < K; ++i) {
                std::tie(nodeNumber, child) = readVocabularyNodeFromFile(fs, K, L - 1, node, nodeNumber);
                node->addChildren(child);
            }
        }

        return std::make_tuple(nodeNumber, node);
    };

    HKMeansNodePtr HKMeansVocabularyBuilder::buildVocabularyNode(cv::Mat data,
                                                                 HKMeansNodeWeakPtr parent,
                                                                 unsigned K, unsigned L) {
        cv::Mat labels, centers;
        cv::kmeans(data, K, labels,
                   cv::TermCriteria(cv::TermCriteria::EPS + cv::TermCriteria::MAX_ITER, 10, 1.0),
                   4, cv::KMEANS_PP_CENTERS, centers);

        auto node = std::make_shared<HKMeansNode>(centers, parent);

        if (L != 0) {
            std::vector<cv::Mat> childrenData(K);
            for (unsigned i = 0; i < labels.rows; ++i) {
                childrenData[labels.at<int>(i)].push_back(data.row(i));
            }

            for (unsigned i = 0; i < K; ++i) {
                node->addChildren(buildVocabularyNode(childrenData[i], node, K, L - 1));
            }
        }

        return node;
    }
}