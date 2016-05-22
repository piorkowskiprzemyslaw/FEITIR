//
// Created by Przemek Piórkowski on 21.05.2016.
//

#include "IndexerBenchmarkDescription.h"

namespace feitir {

    const std::vector<std::string> IndexerBenchmarkDescription::FIELD_NAMES = {/* 0 */ "method",
                                                                               /* 1 */ "database",
                                                                               /* 2 */ "vocabulary_type",
                                                                               /* 3 */ "vocabulary",
                                                                               /* 4 */ "result_file"};

    IndexerBenchmarkDescription::IndexerBenchmarkDescription() : BenchmarkDescription(BenchmarkType::Indexer) { }

    std::vector<std::string> IndexerBenchmarkDescription::getFieldNames() {
        return FIELD_NAMES;
    }

    void IndexerBenchmarkDescription::setBasicPropertiesValues(const std::map<std::string, std::string> valuesMap) {
        this->method = valuesMap.at(FIELD_NAMES[0]);
        this->databasePath = valuesMap.at(FIELD_NAMES[1]);
        this->vocabularyType = valuesMap.at(FIELD_NAMES[2]);
        this->vocabularyPath = valuesMap.at(FIELD_NAMES[3]);
        this->resultFile = valuesMap.at(FIELD_NAMES[4]);
    }

    void IndexerBenchmarkDescription::setCompoundPropertiesValues(
            const std::map<std::string, std::map<std::string, std::string>> compoundProperties) { }

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

    const std::string &IndexerBenchmarkDescription::getVocabularyType() const {
        return vocabularyType;
    }

};