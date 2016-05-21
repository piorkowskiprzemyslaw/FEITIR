//
// Created by Przemek Piórkowski on 21.05.2016.
//

#include "IndexerBenchmarkDescription.h"

namespace feitir {

    const std::vector<std::string> IndexerBenchmarkDescription::FIELD_NAMES = {"method", "database",
                                                                               "vocabulary", "result_file"};

    IndexerBenchmarkDescription::IndexerBenchmarkDescription() : BenchmarkDescription(BenchmarkType::Indexer) { }

    std::vector<std::string> IndexerBenchmarkDescription::getFieldNames() {
        return FIELD_NAMES;
    }

    void IndexerBenchmarkDescription::setPropertiesValues(const std::map<std::string, std::string> valuesMap) {
        this->method = valuesMap.at(FIELD_NAMES[0]);
        this->databasePath = valuesMap.at(FIELD_NAMES[1]);
        this->vocabularyPath = valuesMap.at(FIELD_NAMES[2]);
        this->resultFile = valuesMap.at(FIELD_NAMES[3]);
    }

    const std::string &IndexerBenchmarkDescription::getMethod() const {
        return method;
    }

    const std::string &IndexerBenchmarkDescription::getDatabasePath() const {
        return databasePath;
    }

    const std::string &IndexerBenchmarkDescription::getVocabularyPath() const {
        return vocabularyPath;
    }

    const std::string &IndexerBenchmarkDescription::getResultFile() const {
        return resultFile;
    }
};