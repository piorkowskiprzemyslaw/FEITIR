//
// Created by Przemek Piórkowski on 19.03.2016.
//

#ifndef FEITIR_KMEANSDICTIONARY_H
#define FEITIR_KMEANSDICTIONARY_H

#include <opencv2/core.hpp>
#include <boost/filesystem.hpp>

namespace feitir {

    class KMeansVocabulary {
    public:
        static const std::string VOCABULARY_FILE_NODE;

        explicit KMeansVocabulary();
        cv::Mat create(cv::InputArray data, int K) const noexcept;
        void saveToFile(const cv::Mat vocabulary, const std::string &file) const;
        cv::Mat readFromFile(const std::string & file) const;
    };

}


#endif //FEITIR_KMEANSDICTIONARY_H
