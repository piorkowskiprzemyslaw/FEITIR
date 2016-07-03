//
// Created by Przemek Piórkowski on 21.05.2016.
//

#include <boost/lexical_cast.hpp>
#include <src/main/util/Util.h>
#include "BSIFTBenchmarkDescription.h"

namespace feitir {

    const std::vector<std::string> BSIFTBenchmarkDescription::FIELD_NAMES = {/* 0 */ "database_path",
                                                                             /* 1 */ "vocabulary_type",
                                                                             /* 2 */ "vocabulary_path",
                                                                             /* 3 */ "measure_time",
                                                                             /* 4 */ "result_file",
                                                                             /* 5 */ "a_set_file",
                                                                             /* 6 */ "b_set_file"};

    const std::string BSIFTBenchmarkDescription::BSIFT_METHOD = "bsift_method";

    const std::string &BSIFTBenchmarkDescription::getDatabasePath() const {
        return databasePath;
    }

    const std::string &BSIFTBenchmarkDescription::getVocabularyPath() const {
        return vocabularyPath;
    }

    const std::string &BSIFTBenchmarkDescription::getVocabularyType() const {
        return vocabularyType;
    }

    bool BSIFTBenchmarkDescription::isMeasureTime() const {
        return measureTime;
    }

    const std::string &BSIFTBenchmarkDescription::getResultFile() const {
        return resultFile;
    }

    BSIFTMethodDescriptionPtr BSIFTBenchmarkDescription::getMethodDescription() const {
        return methodDescription;
    }

    const std::vector<unsigned> & BSIFTBenchmarkDescription::getASet() const {
        return aSet;
    }

    const std::vector<unsigned> & BSIFTBenchmarkDescription::getBSet() const {
        return bSet;
    }

    JSONObject::FieldNames BSIFTBenchmarkDescription::basicFieldNames() const {
        return FIELD_NAMES;
    }

    void BSIFTBenchmarkDescription::setBasicFields(const JSONObject::ValuesMap &valuesMap) {
        if (valuesMap.count(FIELD_NAMES[0])) databasePath = valuesMap.at(FIELD_NAMES[0]);
        if (valuesMap.count(FIELD_NAMES[1])) vocabularyType = valuesMap.at(FIELD_NAMES[1]);
        if (valuesMap.count(FIELD_NAMES[2])) vocabularyPath = valuesMap.at(FIELD_NAMES[2]);
        if (valuesMap.count(FIELD_NAMES[3])) measureTime = boost::lexical_cast<bool>(valuesMap.at(FIELD_NAMES[3]));
        if (valuesMap.count(FIELD_NAMES[4])) resultFile = valuesMap.at(FIELD_NAMES[4]);
        if (valuesMap.count(FIELD_NAMES[5])) aSet = Util::fileToElements<unsigned>(valuesMap.at(FIELD_NAMES[5]));
        if (valuesMap.count(FIELD_NAMES[6])) bSet = Util::fileToElements<unsigned>(valuesMap.at(FIELD_NAMES[6]));
    }

    JSONObject::FieldNames BSIFTBenchmarkDescription::innerObjectFieldNames() const {
        return {BSIFT_METHOD};
    }

    std::map<JSONObject::FName, JSONObject::JSONObjectPtr> BSIFTBenchmarkDescription::innerObjectTypes() const {
        return {
                {BSIFT_METHOD, std::make_shared<BSIFTMethodDescription>()}
        };
    }

    void BSIFTBenchmarkDescription::setInnerObjectsField(const JSONObject::InnerObjectsValuesMap &innerObjectsValuesMap) {
        if (innerObjectsValuesMap.count(BSIFT_METHOD))
            methodDescription = std::dynamic_pointer_cast<BSIFTMethodDescription>(innerObjectsValuesMap.at(BSIFT_METHOD));
    }

    JSONObject::JSONObjectPtr BSIFTBenchmarkDescription::constructNewObject() const {
        return std::make_shared<BSIFTBenchmarkDescription>();
    }

}
