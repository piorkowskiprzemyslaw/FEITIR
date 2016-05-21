//
// Created by Przemek Piórkowski on 21.05.2016.
//

#include <boost/lexical_cast.hpp>
#include "BSIFTBenchmarkDescription.h"

namespace feitir {

    const std::vector<std::string> BSIFTBenchmarkDescription::FIELD_NAMES = {"method", "database",
                                                                             "vocabulary", "measure_time",
                                                                             "result_file"};

    BSIFTBenchmarkDescription::BSIFTBenchmarkDescription() : BenchmarkDescription(BenchmarkType::Indexer) { }

    std::vector<std::string> BSIFTBenchmarkDescription::getFieldNames() {
        return FIELD_NAMES;
    }

    void BSIFTBenchmarkDescription::setPropertiesValues(const std::map<std::string, std::string> valuesMap) {
        this->method = valuesMap.at(FIELD_NAMES[0]);
        this->databasePath = valuesMap.at(FIELD_NAMES[1]);
        this->vocabularyPath = valuesMap.at(FIELD_NAMES[2]);
        this->measureTime = boost::lexical_cast<bool>(valuesMap.at(FIELD_NAMES[3]));
        this->resultFile = valuesMap.at(FIELD_NAMES[4]);
    }

    const std::string &BSIFTBenchmarkDescription::getMethod() const {
        return method;
    }

    const std::string &BSIFTBenchmarkDescription::getDatabasePath() const {
        return databasePath;
    }

    const std::string &BSIFTBenchmarkDescription::getVocabularyPath() const {
        return vocabularyPath;
    }

    bool BSIFTBenchmarkDescription::isMeasureTime() const {
        return measureTime;
    }

    const std::string &BSIFTBenchmarkDescription::getResultFile() const {
        return resultFile;
    }
}