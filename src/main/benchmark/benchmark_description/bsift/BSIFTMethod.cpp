//
// Created by przemek on 24.05.16.
//

#include <boost/lexical_cast.hpp>
#include "BSIFTMethod.h"

namespace feitir {
    const std::vector<std::string> BSIFTMethod::FIELD_NAMES = {/* 0 */ "method",
                                                               /* 1 */ "L",
                                                               /* 2 */ "T",
                                                               /* 3 */ "N"};

    const JSONObject::string &BSIFTMethod::getMethod() const {
        return method;
    }

    JSONObject::number BSIFTMethod::getL() const {
        return L;
    }

    JSONObject::number BSIFTMethod::getT() const {
        return T;
    }

    JSONObject::number BSIFTMethod::getN() const {
        return N;
    }

    JSONObject::FieldNames BSIFTMethod::basicFieldNames() const {
        return FIELD_NAMES;
    }

    void BSIFTMethod::setBasicFields(const JSONObject::ValuesMap &valuesMap) {
        if (valuesMap.count(FIELD_NAMES[0])) method = valuesMap.at(FIELD_NAMES[0]);
        if (valuesMap.count(FIELD_NAMES[1])) L = boost::lexical_cast<number>(valuesMap.at(FIELD_NAMES[1]));
        if (valuesMap.count(FIELD_NAMES[2])) T = boost::lexical_cast<number>(valuesMap.at(FIELD_NAMES[2]));
        if (valuesMap.count(FIELD_NAMES[3])) N = boost::lexical_cast<number>(valuesMap.at(FIELD_NAMES[3]));
    }

    JSONObject::JSONObjectPtr BSIFTMethod::constructNewObject() const {
        return std::make_shared<BSIFTMethod>();
    }

}