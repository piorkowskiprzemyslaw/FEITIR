//
// Created by Przemek Piórkowski on 21.05.2016.
//

#include "IndexerBenchmark.h"

namespace feitir {

    const std::vector<std::string> IndexerBenchmark::FIELD_NAMES = { /* 0 */ "database_path",
                                                                     /* 1 */ "result_file"};

    const std::vector<std::string> IndexerBenchmark::OBJECT_NAMES = { /* 0 */"indexer_method",
                                                                      /* 1 */"bsift_algorithm"};

    IndexerMethodPtr IndexerBenchmark::getMethod() const {
        return method;
    }

    const JSONObject::string &IndexerBenchmark::getDatabasePath() const {
        return databasePath;
    }

    const JSONObject::string &IndexerBenchmark::getResultFile() const {
        return resultFile;
    }

    BSIFTAlgorithmPtr IndexerBenchmark::getBsiftAlgorithm() const {
        return bsiftAlgorithm;
    }

    JSONObject::FieldNames IndexerBenchmark::basicFieldNames() const {
        return FIELD_NAMES;
    }

    void IndexerBenchmark::setBasicFields(const JSONObject::ValuesMap &valuesMap) {
        if (valuesMap.count(FIELD_NAMES[0])) databasePath = valuesMap.at(FIELD_NAMES[0]);
        if (valuesMap.count(FIELD_NAMES[1])) resultFile = valuesMap.at(FIELD_NAMES[1]);
    }

    JSONObject::JSONObjectPtr IndexerBenchmark::constructNewObject() const {
        return std::make_shared<IndexerBenchmark>();
    }

    JSONObject::FieldNames IndexerBenchmark::innerObjectFieldNames() const {
        return OBJECT_NAMES;
    }

    std::map<JSONObject::FName, JSONObject::JSONObjectPtr> IndexerBenchmark::innerObjectTypes() const {
        return {
                {OBJECT_NAMES[0], std::make_shared<IndexerMethod>()},
                {OBJECT_NAMES[1], std::make_shared<BSIFTAlgorithm>()}
        };
    }

    void IndexerBenchmark::setInnerObjectsField(const JSONObject::InnerObjectsValuesMap &innerObjectsValuesMap) {
        if (innerObjectsValuesMap.count(OBJECT_NAMES[0]))
            method = std::dynamic_pointer_cast<IndexerMethod>(innerObjectsValuesMap.at(OBJECT_NAMES[0]));
        if (innerObjectsValuesMap.count(OBJECT_NAMES[1]))
            bsiftAlgorithm = std::dynamic_pointer_cast<BSIFTAlgorithm>(innerObjectsValuesMap.at(OBJECT_NAMES[1]));
    }
};