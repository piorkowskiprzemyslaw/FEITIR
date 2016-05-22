//
// Created by Przemek Piórkowski on 19.03.2016.
//

#include "KMeansVocabularyBuilder.h"

namespace feitir {

    const std::string KMeansVocabularyBuilder::VOCABULARY_FILE_NODE = "vocabularyMatrix";

    KMeansVocabularyBuilder::KMeansVocabularyBuilder() { }

    KMeansVocabularyBuilder::~KMeansVocabularyBuilder() { }

    KMeansVocabularyTypePtr KMeansVocabularyBuilder::build(KMeansParameterPtr parameter) {
        cv::Mat labels, centers;
        //TODO think about better adjustment of those parameters
        cv::kmeans(parameter->getData(), parameter->getK(), labels,
                   cv::TermCriteria(cv::TermCriteria::MAX_ITER + cv::TermCriteria::EPS, 10, 1.0),
                   4, cv::KMEANS_PP_CENTERS, centers);
        return std::make_shared<KMeansVocabularyType>(centers);
    }

    void KMeansVocabularyBuilder::saveToFile(KMeansVocabularyTypePtr vocabulary, const std::string &file) const {
        if (!boost::filesystem::exists(file)) {
            cv::FileStorage fs(file.c_str(), cv::FileStorage::WRITE);
            cv::write(fs, VOCABULARY_FILE_NODE, vocabulary->getVocabularyMatrix());
            fs.release();
        }
    }

    KMeansVocabularyTypePtr KMeansVocabularyBuilder::readFromFile(const std::string &file) const {
        cv::Mat vocabulary;
        if (boost::filesystem::exists(file)) {
            cv::FileStorage fs(file.c_str(), cv::FileStorage::READ);
            cv::read(fs[VOCABULARY_FILE_NODE], vocabulary);
            fs.release();
        }
        return std::make_shared<KMeansVocabularyType>(vocabulary);
    }
}