//
// Created by Przemek Piórkowski on 24.07.2016.
//

#include "BSIFTAlgorithm.h"

namespace feitir {

    const std::string BSIFTAlgorithm::BSIFT_METHOD = "bsift_method";

    const std::vector<std::string> BSIFTAlgorithm::FIELD_NAMES = { /* 0 */ "database_path",
                                                                   /* 1 */ "vocabulary_path",
                                                                   /* 2 */ "vocabulary_type"};

    const JSONObject::string &BSIFTAlgorithm::getDatabasePath() const {
        return databasePath;
    }

    const JSONObject::string &BSIFTAlgorithm::getVocabularyPath() const {
        return vocabularyPath;
    }

    const JSONObject::string &BSIFTAlgorithm::getVocabularyType() const {
        return vocabularyType;
    }

    const BSIFTMethodDescriptionPtr &BSIFTAlgorithm::getBsiftMethod() const {
        return bsiftMethodDescriptionPtr;
    }

    JSONObject::JSONObjectPtr BSIFTAlgorithm::constructNewObject() const {
        return std::make_shared<BSIFTAlgorithm>();
    }

    JSONObject::FieldNames BSIFTAlgorithm::basicFieldNames() const {
        return FIELD_NAMES;
    }

    void BSIFTAlgorithm::setBasicFields(const JSONObject::ValuesMap &valuesMap) {
        if (valuesMap.count(FIELD_NAMES[0])) databasePath = valuesMap.at(FIELD_NAMES[0]);
        if (valuesMap.count(FIELD_NAMES[1])) vocabularyPath = valuesMap.at(FIELD_NAMES[1]);
        if (valuesMap.count(FIELD_NAMES[2])) vocabularyType = valuesMap.at(FIELD_NAMES[2]);
    }

    JSONObject::FieldNames BSIFTAlgorithm::innerObjectFieldNames() const {
        return {BSIFT_METHOD};
    }

    std::map<JSONObject::FName, JSONObject::JSONObjectPtr> BSIFTAlgorithm::innerObjectTypes() const {
        return {
                {BSIFT_METHOD, std::make_shared<BSIFTMethodDescription>()}
        };
    }

    void BSIFTAlgorithm::setInnerObjectsField(const JSONObject::InnerObjectsValuesMap &innerObjectsValuesMap) {
        if (innerObjectsValuesMap.count(BSIFT_METHOD))
            bsiftMethodDescriptionPtr =
                    std::dynamic_pointer_cast<BSIFTMethodDescription>(innerObjectsValuesMap.at(BSIFT_METHOD));
    }
}