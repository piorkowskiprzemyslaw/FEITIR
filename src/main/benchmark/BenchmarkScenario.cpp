//
// Created by Przemek Piórkowski on 19.05.2016.
//

#include "BenchmarkScenario.h"

namespace feitir {

    const std::string BenchmarkScenario::BSIFT_BENCHMARKS = "bsift_benchmarks";
    const std::string BenchmarkScenario::INDEXER_BENCHMARKS = "indexer_benchmarks";

    const std::vector<BSIFTBenchmarkPtr> &BenchmarkScenario::getBsiftBenchmarkDescriptions() const {
        return bsiftBenchmarkDescriptions;
    }

    const std::vector<IndexerBenchmarkPtr> &BenchmarkScenario::getIndexerBenchmarkDescriptions() const {
        return indexerBenchmarkDescriptions;
    }

    JSONObject::JSONObjectPtr BenchmarkScenario::constructNewObject() const {
        return std::make_shared<BenchmarkScenario>();
    }

    JSONObject::FieldNames BenchmarkScenario::arrayOfObjectsFieldNames() const {
        return {BSIFT_BENCHMARKS, INDEXER_BENCHMARKS};
    }

    std::map<JSONObject::FName, JSONObject::JSONObjectPtr> BenchmarkScenario::arrayOfObjectTypes() const {
        return {
                {BSIFT_BENCHMARKS, std::make_shared<BSIFTBenchmark>()},
                {INDEXER_BENCHMARKS, std::make_shared<IndexerBenchmark>()} };
    }

    void BenchmarkScenario::setArrayOfObjectsField(const JSONObject::ArrayObjectsValuesMap &arrayObjectsValuesMap) {
        if (arrayObjectsValuesMap.count(BSIFT_BENCHMARKS)) {
            bsiftBenchmarkDescriptions.clear();
            auto bsiftVector = arrayObjectsValuesMap.at(BSIFT_BENCHMARKS);
            std::transform(bsiftVector.begin(), bsiftVector.end(), back_inserter(bsiftBenchmarkDescriptions),
                           [] (const JSONObjectPtr &objectPtr) {
                               return std::dynamic_pointer_cast<BSIFTBenchmark>(objectPtr);
                           });
        }

        if (arrayObjectsValuesMap.count(INDEXER_BENCHMARKS)) {
            indexerBenchmarkDescriptions.clear();
            auto indexerVector = arrayObjectsValuesMap.at(INDEXER_BENCHMARKS);
            std::transform(indexerVector.begin(), indexerVector.end(), back_inserter(indexerBenchmarkDescriptions),
                           [] (const JSONObjectPtr &objectPtr) {
                               return std::dynamic_pointer_cast<IndexerBenchmark>(objectPtr);
                           });
        }
    }
}