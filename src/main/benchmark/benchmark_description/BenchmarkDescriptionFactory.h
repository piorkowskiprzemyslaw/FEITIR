//
// Created by Przemek Piórkowski on 21.05.2016.
//

#ifndef FEITIR_BENCHMARKDESCRIPTIONFACTORY_H
#define FEITIR_BENCHMARKDESCRIPTIONFACTORY_H

#include <boost/property_tree/ptree.hpp>
#include "src/main/benchmark/BenchmarkDescription.h"
#include "IndexerBenchmarkDescription.h"
#include "BSIFTBenchmarkDescription.h"

namespace feitir {

    class BSIFTBenchmarkDescriptionFactory {
    public:
        BSIFTBenchmarkDescriptionPtr fromPtree(const boost::property_tree::ptree& ptree);
    };

    class IndexerBenchmarkDescriptionFactory {
    public:
        IndexerBenchmarkDescriptionPtr fromPtree(const boost::property_tree::ptree& ptree);
    };

    class BenchmarkDescriptionFactory {
    public:
        BenchmarkDescriptionPtr fromPtree(const boost::property_tree::ptree& ptree);

    private:
        BSIFTBenchmarkDescriptionFactory bsiftFactory;
        IndexerBenchmarkDescriptionFactory indexerFactory;
    };
}


#endif //FEITIR_BENCHMARKDESCRIPTIONFACTORY_H
