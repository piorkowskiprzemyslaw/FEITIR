//
// Created by Przemek Piórkowski on 18.04.2016.
//

#include "HKMeansConfig.h"

namespace feitir {

    HKMeansParameter::HKMeansParameter(cv::Mat data, const unsigned K, const unsigned L)
            : data{data}, K{K}, L{L} { }

    HKMeansParameter::HKMeansParameter(const DatabasePtr database, const unsigned K, const unsigned L) : K{K}, L{L} {
        for (auto img : *database)
            data.push_back(img->getDescriptors());
    }

    const cv::Mat HKMeansParameter::getData() const {
        return data;
    }

    const unsigned HKMeansParameter::getK() const {
        return K;
    }

    const unsigned int HKMeansParameter::getL() const {
        return L;
    }

    HKMeansVocabularyType::HKMeansVocabularyType(HKMeansNodePtr root, unsigned K, unsigned L)
            : root{root}, K{K}, L{L} {
        vocabularyMatrix = getVocabulary(root);
    }

    cv::Mat HKMeansVocabularyType::getVocabulary(HKMeansNodePtr root) {
        if (root->getChildrens().empty()) {
            // leaf node
            return root->getNodeWords();
        }

        cv::Mat childrenNodesWords;
        for (auto child : root->getChildrens()) {
            childrenNodesWords.push_back(getVocabulary(child));
        }
        return childrenNodesWords;
    }

    cv::Mat HKMeansVocabularyType::getVocabularyMatrix() const {
        return vocabularyMatrix;
    }

    HKMeansNode::HKMeansNode(const cv::Mat nodeWords,
                             const HKMeansNodeWeakPtr parent) : nodeWords{nodeWords},
                                                                parent{parent} { }

    const cv::Mat HKMeansNode::getNodeWords() const {
        return nodeWords;
    }

    void HKMeansNode::addChildren(HKMeansNodePtr child) {
        childrens.push_back(child);
    }

    const std::vector<HKMeansNodePtr> & HKMeansNode::getChildrens() const {
        return childrens;
    }

    const HKMeansNodeWeakPtr HKMeansNode::getParent() const {
        return parent;
    }

    const HKMeansNodePtr HKMeansVocabularyType::getRoot() const {
        return root;
    }

    unsigned int HKMeansVocabularyType::getK() const {
        return K;
    }

    unsigned int HKMeansVocabularyType::getL() const {
        return L;
    }
}