//
// Created by Przemek Piórkowski on 21.05.2016.
//

#include "IndexerBenchmarkDescription.h"

namespace feitir {

    const std::vector<std::string> IndexerBenchmarkDescription::FIELD_NAMES = {/* 0 */ "method",
                                                                               /* 1 */ "database_path",
                                                                               /* 2 */ "vocabulary_type",
                                                                               /* 3 */ "vocabulary_path",
                                                                               /* 4 */ "result_file"};

    const std::string &IndexerBenchmarkDescription::getMethod() const {
        return method;
    }

    const std::string &IndexerBenchmarkDescription::getDatabasePath() const {
        return databasePath;
    }

    const std::string &IndexerBenchmarkDescription::getVocabularyType() const {
        return vocabularyType;
    }

    const std::string &IndexerBenchmarkDescription::getVocabularyPath() const {
        return vocabularyPath;
    }

    const std::string &IndexerBenchmarkDescription::getResultFile() const {
        return resultFile;
    }

    JSONObject::FieldNames IndexerBenchmarkDescription::basicFieldNames() const {
        return FIELD_NAMES;
    }

    void IndexerBenchmarkDescription::setBasicFields(const JSONObject::ValuesMap &valuesMap) {
        if (valuesMap.count(FIELD_NAMES[0]))  method = valuesMap.at(FIELD_NAMES[0]);
        if (valuesMap.count(FIELD_NAMES[1])) databasePath = valuesMap.at(FIELD_NAMES[1]);
        if (valuesMap.count(FIELD_NAMES[2])) vocabularyType = valuesMap.at(FIELD_NAMES[2]);
        if (valuesMap.count(FIELD_NAMES[3])) vocabularyPath = valuesMap.at(FIELD_NAMES[3]);
        if (valuesMap.count(FIELD_NAMES[4])) resultFile = valuesMap.at(FIELD_NAMES[4]);
    }

    JSONObject::JSONObjectPtr IndexerBenchmarkDescription::constructNewObject() const {
        return std::make_shared<IndexerBenchmarkDescription>();
    }
};