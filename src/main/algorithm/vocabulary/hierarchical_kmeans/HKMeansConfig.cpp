//
// Created by Przemek Piórkowski on 18.04.2016.
//

#include "HKMeansConfig.h"
#include "thread"

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

    bool HKMeansNode::operator==(const HKMeansNode& rhs) const {
        if (cv::countNonZero(rhs.nodeWords != nodeWords) != 0 || rhs.childrens.size() != childrens.size()) {
            return false;
        }

        for (int i = 0; i < childrens.size(); ++i) {
            if (*(childrens[i]) != *(rhs.childrens[i])) {
                return false;
            }
        }

        return true;
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

    bool HKMeansVocabularyType::operator==(const HKMeansVocabularyType& rhs) const {
        return (rhs.K == K) && (rhs.L == L) && (*(rhs.root) == *root);
    }

    std::vector<cv::DMatch> HKMeansVocabularyType::getNearestVisualWords(cv::Mat queryFeatures) {
        unsigned numberOfThreads = std::thread::hardware_concurrency() > 0 ? std::thread::hardware_concurrency() : 4;

        if (numberOfThreads < queryFeatures.rows) {
            return getNearestVisualWordsConcurrent(queryFeatures, numberOfThreads);
        } else {
            std::vector<cv::DMatch> matches;
            matcher.match(queryFeatures, vocabularyMatrix, matches);
            return matches;
        }
    }

    std::vector<cv::DMatch> HKMeansVocabularyType::getNearestVisualWordsConcurrent(cv::Mat queryFeatures,
                                                                                   unsigned numberOfThreads) {
        std::vector<std::thread> threads;
        std::vector<cv::DMatch> resultVector(queryFeatures.rows);
        unsigned x = queryFeatures.rows / numberOfThreads;
        unsigned rest = queryFeatures.rows % numberOfThreads;
        unsigned currentIdx = 0;

        auto fun = [this] (cv::Mat features, std::vector<cv::DMatch> &resultVec,
                           unsigned startIdx, unsigned endIdx) {
            for (auto i = startIdx; i < endIdx; ++i) {
                resultVec[i] = this->getNearestVisualWord(this->root, features.row(i));
            }
        };

        for (int i = 0; i < numberOfThreads; ++i) {
            if (i < rest) {
                threads.push_back(std::thread(fun, queryFeatures, std::ref(resultVector), currentIdx, currentIdx + x + 1));
                currentIdx = currentIdx + x + 1;
            } else {
                threads.push_back(std::thread(fun, queryFeatures, std::ref(resultVector), currentIdx, currentIdx + x));
                currentIdx = currentIdx + x;
            }
        }

        for (std::thread &t : threads) {
            t.join();
        }

        assert (currentIdx == resultVector.size());
        return resultVector;
    }

    cv::DMatch HKMeansVocabularyType::getNearestVisualWord(HKMeansNodePtr root, cv::Mat queryFeature) {
        assert (queryFeature.rows == 1);
        std::vector<cv::DMatch> matches;
        matcher.match(queryFeature, root->getNodeWords(), matches);
        assert (matches.size() == 1);
        cv::DMatch match = matches[0];

        if (root->getChildrens().empty()) {
            return match;
        } else {
            return getNearestVisualWord(root->getChildrens()[match.trainIdx], queryFeature);
        }

    }
}