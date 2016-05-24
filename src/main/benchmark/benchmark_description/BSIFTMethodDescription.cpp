//
// Created by przemek on 24.05.16.
//

#include <boost/lexical_cast.hpp>
#include "BSIFTMethodDescription.h"

namespace feitir {
    const std::vector<std::string> BSIFTMethodDescription::FIELD_NAMES = {/* 0 */ "method",
                                                                          /* 1 */ "L",
                                                                          /* 2 */ "T"};

    const std::string &BSIFTMethodDescription::getMethod() const {
        return method;
    }

    int BSIFTMethodDescription::getL() const {
        return L;
    }

    int BSIFTMethodDescription::getT() const {
        return T;
    }

    JSONObject::FieldNames BSIFTMethodDescription::basicFieldNames() const {
        return FIELD_NAMES;
    }

    void BSIFTMethodDescription::setBasicFields(const JSONObject::ValuesMap &valuesMap) {
        if (valuesMap.count(FIELD_NAMES[0])) method = valuesMap.at(FIELD_NAMES[0]);
        if (valuesMap.count(FIELD_NAMES[1])) L = boost::lexical_cast<int>(valuesMap.at(FIELD_NAMES[1]));
        if (valuesMap.count(FIELD_NAMES[2])) T = boost::lexical_cast<int>(valuesMap.at(FIELD_NAMES[2]));
    }

    JSONObject::JSONObjectPtr BSIFTMethodDescription::constructNewObject() const {
        return std::make_shared<BSIFTMethodDescription>();
    }
}