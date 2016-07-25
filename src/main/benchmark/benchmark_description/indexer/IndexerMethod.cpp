//
// Created by Przemek Piórkowski on 21.07.2016.
//

#include <boost/lexical_cast.hpp>
#include "IndexerMethod.h"

namespace feitir {

    const std::vector<std::string> IndexerMethod::FIELD_NAMES = { /* 0 */ "method",
                                                                  /* 1 */  "vocabulary_path",
                                                                  /* 2 */  "vocabulary_type",
                                                                  /* 3 */  "treshold",
                                                                  /* 4 */  "K",
                                                                  /* 5 */  "N",
                                                                  /* 6 */  "R",
                                                                  /* 7 */  "code_word_size"};

    JSONObject::JSONObjectPtr IndexerMethod::constructNewObject() const {
        return std::make_shared<IndexerMethod>();
    }

    JSONObject::FieldNames IndexerMethod::basicFieldNames() const {
        return FIELD_NAMES;
    }

    void IndexerMethod::setBasicFields(const JSONObject::ValuesMap &valuesMap) {
        if (valuesMap.count(FIELD_NAMES[0])) methodName = valuesMap.at(FIELD_NAMES[0]);
        if (valuesMap.count(FIELD_NAMES[1])) vocabularyPath = valuesMap.at(FIELD_NAMES[1]);
        if (valuesMap.count(FIELD_NAMES[2])) vocabularyType = valuesMap.at(FIELD_NAMES[2]);
        if (valuesMap.count(FIELD_NAMES[3])) treshold = boost::lexical_cast<number>(valuesMap.at(FIELD_NAMES[3]));
        if (valuesMap.count(FIELD_NAMES[4])) K = boost::lexical_cast<number>(valuesMap.at(FIELD_NAMES[4]));
        if (valuesMap.count(FIELD_NAMES[5])) N = boost::lexical_cast<number>(valuesMap.at(FIELD_NAMES[5]));
        if (valuesMap.count(FIELD_NAMES[6])) R = boost::lexical_cast<number>(valuesMap.at(FIELD_NAMES[6]));
        if (valuesMap.count(FIELD_NAMES[7])) codeWordSize = boost::lexical_cast<number>(valuesMap.at(FIELD_NAMES[7]));
    }

    const JSONObject::string &IndexerMethod::getMethodName() const {
        return methodName;
    }

    const JSONObject::string &IndexerMethod::getVocabularyPath() const {
        return vocabularyPath;
    }

    const JSONObject::string &IndexerMethod::getVocabularyType() const {
        return vocabularyType;
    }

    JSONObject::number IndexerMethod::getTreshold() const {
        return treshold;
    }

    JSONObject::number IndexerMethod::getK() const {
        return K;
    }

    JSONObject::number IndexerMethod::getN() const {
        return N;
    }

    JSONObject::number IndexerMethod::getR() const {
        return R;
    }

    JSONObject::number IndexerMethod::getCodeWordSize() const {
        return codeWordSize;
    }
}