//
// Created by Przemek Piórkowski on 19.05.2016.
//

#ifndef FEITIR_BENCHMARKSCENARIO_H
#define FEITIR_BENCHMARKSCENARIO_H

#include <iostream>
#include <boost/program_options.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <src/main/benchmark/benchmark_description/bsift/BSIFTBenchmark.h>
#include <src/main/benchmark/benchmark_description/indexer/IndexerBenchmark.h>
#include "src/main/util/JSON/JSONObject.h"

namespace feitir {
    class BenchmarkScenario : public JSONObject {
    public:
        const std::vector<BSIFTBenchmarkPtr> & getBsiftBenchmarkDescriptions() const;
        const std::vector<IndexerBenchmarkPtr> & getIndexerBenchmarkDescriptions() const;

    protected:
        virtual FieldNames arrayOfObjectsFieldNames() const override;
        virtual std::map<FName, JSONObjectPtr> arrayOfObjectTypes() const override;
        virtual void setArrayOfObjectsField(const ArrayObjectsValuesMap &arrayObjectsValuesMap) override;
        virtual JSONObjectPtr constructNewObject() const override;

    private:
        static const std::string BSIFT_BENCHMARKS;
        static const std::string INDEXER_BENCHMARKS;

        std::vector<BSIFTBenchmarkPtr> bsiftBenchmarkDescriptions;
        std::vector<IndexerBenchmarkPtr> indexerBenchmarkDescriptions;
    };

    using BenchmarkScenarioPtr = std::shared_ptr<BenchmarkScenario>;

}


#endif //FEITIR_BENCHMARKSCENARIO_H
