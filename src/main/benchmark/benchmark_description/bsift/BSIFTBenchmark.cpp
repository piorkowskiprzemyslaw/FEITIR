//
// Created by Przemek Piórkowski on 21.05.2016.
//

#include <boost/lexical_cast.hpp>
#include <src/main/util/Util.h>
#include "BSIFTBenchmark.h"

namespace feitir {

    const std::vector<std::string> BSIFTBenchmark::FIELD_NAMES = { /* 0 */ "database_path",
                                                                   /* 1 */ "measure_time",
                                                                   /* 2 */ "result_file",
                                                                   /* 3 */ "a_set_file",
                                                                   /* 4 */ "b_set_file"};

    const std::string BSIFTBenchmark::BSIFT_ALGORITHM = "bsift_algorithm";

    const JSONObject::string &BSIFTBenchmark::getDatabasePath() const {
        return databasePath;
    }

    JSONObject::boolean BSIFTBenchmark::isMeasureTime() const {
        return measureTime;
    }

    const BSIFTAlgorithmPtr &BSIFTBenchmark::getAlgorithm() const {
        return algorithm;
    }

    const JSONObject::string &BSIFTBenchmark::getResultFile() const {
        return resultFile;
    }

    const std::vector<JSONObject::number> & BSIFTBenchmark::getASet() const {
        return aSet;
    }

    const std::vector<JSONObject::number> & BSIFTBenchmark::getBSet() const {
        return bSet;
    }

    JSONObject::FieldNames BSIFTBenchmark::basicFieldNames() const {
        return FIELD_NAMES;
    }

    void BSIFTBenchmark::setBasicFields(const JSONObject::ValuesMap &valuesMap) {
        if (valuesMap.count(FIELD_NAMES[0])) databasePath = valuesMap.at(FIELD_NAMES[0]);
        if (valuesMap.count(FIELD_NAMES[1])) measureTime = boost::lexical_cast<boolean>(valuesMap.at(FIELD_NAMES[1]));
        if (valuesMap.count(FIELD_NAMES[2])) resultFile = valuesMap.at(FIELD_NAMES[2]);
        if (valuesMap.count(FIELD_NAMES[3])) aSet = Util::fileToElements<number>(valuesMap.at(FIELD_NAMES[3]));
        if (valuesMap.count(FIELD_NAMES[4])) bSet = Util::fileToElements<number>(valuesMap.at(FIELD_NAMES[4]));
    }

    JSONObject::FieldNames BSIFTBenchmark::innerObjectFieldNames() const {
        return {BSIFT_ALGORITHM};
    }

    std::map<JSONObject::FName, JSONObject::JSONObjectPtr> BSIFTBenchmark::innerObjectTypes() const {
        return {
                {BSIFT_ALGORITHM, std::make_shared<BSIFTAlgorithm>()}
        };
    }

    void BSIFTBenchmark::setInnerObjectsField(const JSONObject::InnerObjectsValuesMap &innerObjectsValuesMap) {
        if (innerObjectsValuesMap.count(BSIFT_ALGORITHM))
            algorithm = std::dynamic_pointer_cast<BSIFTAlgorithm>(innerObjectsValuesMap.at(BSIFT_ALGORITHM));
    }

    JSONObject::JSONObjectPtr BSIFTBenchmark::constructNewObject() const {
        return std::make_shared<BSIFTBenchmark>();
    }

}
