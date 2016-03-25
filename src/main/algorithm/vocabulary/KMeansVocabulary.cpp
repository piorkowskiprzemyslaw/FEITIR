//
// Created by Przemek Piórkowski on 19.03.2016.
//

#include "KMeansVocabulary.h"

namespace feitir {

    const std::string KMeansVocabulary::VOCABULARY_FILE_NODE = "vocabulary";

    KMeansVocabulary::KMeansVocabulary() { }

    cv::Mat KMeansVocabulary::create(cv::InputArray data, int K) const noexcept {
        cv::Mat labels, centers;
        //TODO think about better adjustment of those parameters
        cv::kmeans(data, K, labels, cv::TermCriteria(cv::TermCriteria::EPS, 10, 1.0), 10, cv::KMEANS_PP_CENTERS, centers);
        return centers;
    }

    cv::Mat KMeansVocabulary::readFromFile(const std::string &file) const {
        cv::Mat vocabulary;
        if (boost::filesystem::exists(file)) {
            cv::FileStorage fs(file.c_str(), cv::FileStorage::READ);
            cv::read(fs[VOCABULARY_FILE_NODE], vocabulary);
            fs.release();
        }
        return vocabulary;
    }


    void KMeansVocabulary::saveToFile(const cv::Mat vocabulary, const std::string &file) const {
        if (!boost::filesystem::exists(file)) {
            cv::FileStorage fs(file.c_str(), cv::FileStorage::WRITE);
            cv::write(fs, VOCABULARY_FILE_NODE, vocabulary);
            fs.release();
        }
    }


}