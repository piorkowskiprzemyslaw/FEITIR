//
// Created by Przemek Piórkowski on 21.05.2016.
//

#include <boost/lexical_cast.hpp>
#include "BSIFTBenchmarkDescription.h"

namespace feitir {

    /** BSIFTMethodDescription **/

    const std::vector<std::string> BSIFTMethodDescription::FIELD_NAMES = {/* 0 */ "method",
                                                                          /* 1 */ "L",
                                                                          /* 2 */ "T"};

    void BSIFTMethodDescription::setBasicPropertiesValues(const std::map<std::string, std::string> valuesMap) {
        this->method = valuesMap.at(FIELD_NAMES[0]);
        this->L = boost::lexical_cast<int>(valuesMap.at(FIELD_NAMES[1]));
        this->T = boost::lexical_cast<int>(valuesMap.at(FIELD_NAMES[2]));
    }

    std::vector<std::string> BSIFTMethodDescription::getFieldNames() {
        return FIELD_NAMES;
    }

    const std::string &BSIFTMethodDescription::getMethod() const {
        return method;
    }

    int BSIFTMethodDescription::getT() const {
        return T;
    }

    int BSIFTMethodDescription::getL() const {
        return L;
    }

    /** BSIFTBenchmarkDescription **/

    const std::vector<std::string> BSIFTBenchmarkDescription::FIELD_NAMES = {/* 0 */ "database",
                                                                             /* 1 */ "vocabulary_type",
                                                                             /* 2 */ "vocabulary",
                                                                             /* 3 */ "measure_time",
                                                                             /* 4 */ "result_file"};

    const std::map<std::string, std::vector<std::string>> BSIFTBenchmarkDescription::COMPOUND_FIELDS = {
            {"method_description", BSIFTMethodDescription::getFieldNames()}};

    BSIFTBenchmarkDescription::BSIFTBenchmarkDescription() : BenchmarkDescription(BenchmarkType::Indexer) { }

    std::vector<std::string> BSIFTBenchmarkDescription::getFieldNames() {
        return FIELD_NAMES;
    }

    std::map<std::string, std::vector<std::string>> BSIFTBenchmarkDescription::getCompoundFieldsNames() {
        return COMPOUND_FIELDS;
    }

    void BSIFTBenchmarkDescription::setBasicPropertiesValues(const std::map<std::string, std::string> valuesMap) {
        this->databasePath = valuesMap.at(FIELD_NAMES[0]);
        this->vocabularyType = valuesMap.at(FIELD_NAMES[1]);
        this->vocabularyPath = valuesMap.at(FIELD_NAMES[2]);
        this->measureTime = boost::lexical_cast<bool>(valuesMap.at(FIELD_NAMES[3]));
        this->resultFile = valuesMap.at(FIELD_NAMES[4]);
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

    const std::string &BSIFTBenchmarkDescription::getVocabularyType() const {
        return vocabularyType;
    }

    void BSIFTBenchmarkDescription::setCompoundPropertiesValues(
            const std::map<std::string, std::map<std::string, std::string>> compoundProperties) {
        methodDescription.setBasicPropertiesValues(compoundProperties.at("method_description"));
    }

    const BSIFTMethodDescription &BSIFTBenchmarkDescription::getMethodDescription() const {
        return methodDescription;
    }

}
