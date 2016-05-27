//
// Created by przemek on 24.05.16.
//

#include <boost/lexical_cast.hpp>
#include "BSIFTMethodDescription.h"

namespace feitir {
    const std::vector<std::string> BSIFTMethodDescription::FIELD_NAMES = {/* 0 */ "method",
                                                                          /* 1 */ "L",
                                                                          /* 2 */ "T",
                                                                          /* 3 */ "N"};

    const std::string &BSIFTMethodDescription::getMethod() const {
        return method;
    }

    int BSIFTMethodDescription::getL() const {
        return L;
    }

    int BSIFTMethodDescription::getT() const {
        return T;
    }

    int BSIFTMethodDescription::getN() const {
        return N;
    }

    JSONObject::FieldNames BSIFTMethodDescription::basicFieldNames() const {
        return FIELD_NAMES;
    }

    void BSIFTMethodDescription::setBasicFields(const JSONObject::ValuesMap &valuesMap) {
        if (valuesMap.count(FIELD_NAMES[0])) method = valuesMap.at(FIELD_NAMES[0]);
        if (valuesMap.count(FIELD_NAMES[1])) L = boost::lexical_cast<int>(valuesMap.at(FIELD_NAMES[1]));
        if (valuesMap.count(FIELD_NAMES[2])) T = boost::lexical_cast<int>(valuesMap.at(FIELD_NAMES[2]));
        if (valuesMap.count(FIELD_NAMES[3])) N = boost::lexical_cast<int>(valuesMap.at(FIELD_NAMES[3]));
    }

    JSONObject::JSONObjectPtr BSIFTMethodDescription::constructNewObject() const {
        return std::make_shared<BSIFTMethodDescription>();
    }

}