//
// Created by Przemek Piórkowski on 19.05.2016.
//

#ifndef FEITIR_BENCHMARKSCENARIO_H
#define FEITIR_BENCHMARKSCENARIO_H

#include <iostream>
#include <boost/program_options.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <src/main/benchmark/benchmark_description/BSIFTBenchmarkDescription.h>
#include <src/main/benchmark/benchmark_description/IndexerBenchmarkDescription.h>
#include "src/main/util/JSON/JSONObject.h"

namespace feitir {
    class BenchmarkScenario : public JSONObject {
    public:
        const std::vector<BSIFTBenchmarkDescriptionPtr> & getBsiftBenchmarkDescriptions() const;
        const std::vector<IndexerBenchmarkDescriptionPtr> & getIndexerBenchmarkDescriptions() const;

    protected:
        virtual FieldNames arrayOfObjectsFieldNames() const override;
        virtual std::map<FName, JSONObjectPtr> arrayOfObjectTypes() const override;
        virtual void setArrayOfObjectsField(const ArrayObjectsValuesMap &arrayObjectsValuesMap) override;
        virtual JSONObjectPtr constructNewObject() const override;

    private:
        static const std::string BSIFT_BENCHMARKS;
        static const std::string INDEXER_BENCHMARKS;

        std::vector<BSIFTBenchmarkDescriptionPtr> bsiftBenchmarkDescriptions;
        std::vector<IndexerBenchmarkDescriptionPtr> indexerBenchmarkDescriptions;
    };

    using BenchmarkScenarioPtr = std::shared_ptr<BenchmarkScenario>;

}


#endif //FEITIR_BENCHMARKSCENARIO_H
