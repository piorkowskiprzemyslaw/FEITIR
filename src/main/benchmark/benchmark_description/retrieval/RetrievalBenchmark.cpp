//
// Created by Przemek Piórkowski on 15.08.2016.
//

#include <boost/lexical_cast.hpp>
#include "RetrievalBenchmark.h"

namespace feitir {

    const std::vector<std::string> RetrievalBenchmark::FIELD_NAMES = { /* 0 */ "test_database_path",
                                                                       /* 1 */ "result_file",
                                                                       /* 2 */ "matching_method",
                                                                       /* 3 */ "time_measure",
                                                                       /* 4 */ "top_query_results"};

    const std::vector<std::string> RetrievalBenchmark::OBJECT_NAMES = { /* 0 */"indexer_method",
                                                                        /* 1 */"bsift_algorithm"};

    JSONObject::FieldNames RetrievalBenchmark::basicFieldNames() const {
        return FIELD_NAMES;
    }

    void RetrievalBenchmark::setBasicFields(const JSONObject::ValuesMap &valuesMap) {
        if (valuesMap.count(FIELD_NAMES[0])) testDatabasePath = valuesMap.at(FIELD_NAMES[0]);
        if (valuesMap.count(FIELD_NAMES[1])) resultFile = valuesMap.at(FIELD_NAMES[1]);
        if (valuesMap.count(FIELD_NAMES[2])) matchingMethod = valuesMap.at(FIELD_NAMES[2]);
        if (valuesMap.count(FIELD_NAMES[3])) timeMeasure = boost::lexical_cast<boolean>(valuesMap.at(FIELD_NAMES[3]));
        if (valuesMap.count(FIELD_NAMES[4])) topQueryResults = boost::lexical_cast<number>(valuesMap.at(FIELD_NAMES[4]));
    }

    JSONObject::FieldNames RetrievalBenchmark::innerObjectFieldNames() const {
        return OBJECT_NAMES;
    }

    std::map<JSONObject::FName, JSONObject::JSONObjectPtr> RetrievalBenchmark::innerObjectTypes() const {
        return {
                {OBJECT_NAMES[0], std::make_shared<IndexerMethod>()},
                {OBJECT_NAMES[1], std::make_shared<BSIFTAlgorithm>()}
        };
    }

    void RetrievalBenchmark::setInnerObjectsField(const JSONObject::InnerObjectsValuesMap &innerObjectsValuesMap) {
        if (innerObjectsValuesMap.count(OBJECT_NAMES[0])) {
            indexerMethod = std::dynamic_pointer_cast<IndexerMethod>(innerObjectsValuesMap.at(OBJECT_NAMES[0]));
        }

        if (innerObjectsValuesMap.count(OBJECT_NAMES[1])) {
            bsiftAlgorithm = std::dynamic_pointer_cast<BSIFTAlgorithm>(innerObjectsValuesMap.at(OBJECT_NAMES[1]));
        }
    }

    JSONObject::JSONObjectPtr RetrievalBenchmark::constructNewObject() const {
        return std::make_shared<RetrievalBenchmark>();
    }

    const JSONObject::string &RetrievalBenchmark::getTestDatabasePath() const {
        return testDatabasePath;
    }

    const JSONObject::string &RetrievalBenchmark::getResultFile() const {
        return resultFile;
    }

    const JSONObject::string &RetrievalBenchmark::getMatchingMethod() const {
        return matchingMethod;
    }

    JSONObject::boolean RetrievalBenchmark::getTimeMeasure() const {
        return timeMeasure;
    }

    const IndexerMethodPtr &RetrievalBenchmark::getIndexerMethod() const {
        return indexerMethod;
    }

    const BSIFTAlgorithmPtr &RetrievalBenchmark::getBsiftAlgorithm() const {
        return bsiftAlgorithm;
    }

    JSONObject::number RetrievalBenchmark::getTopQueryResults() const {
        return topQueryResults;
    }

}