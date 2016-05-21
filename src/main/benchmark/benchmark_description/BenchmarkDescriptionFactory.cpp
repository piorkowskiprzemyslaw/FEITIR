//
// Created by Przemek Piórkowski on 21.05.2016.
//

#include "BenchmarkDescriptionFactory.h"

namespace feitir {

    BSIFTBenchmarkDescriptionPtr BSIFTBenchmarkDescriptionFactory::fromPtree(const boost::property_tree::ptree &ptree) {
        std::map<std::string, std::string> fieldValues;
        for (const auto& field: BSIFTBenchmarkDescription::getFieldNames()) {
            fieldValues.insert({field, ptree.get<std::string>(field)});
        }
        BSIFTBenchmarkDescriptionPtr benchmarkDescriptionPtr = std::make_shared<BSIFTBenchmarkDescription>();
        benchmarkDescriptionPtr->setPropertiesValues(fieldValues);
        return benchmarkDescriptionPtr;
    }

    IndexerBenchmarkDescriptionPtr IndexerBenchmarkDescriptionFactory::fromPtree(const boost::property_tree::ptree &ptree) {
        std::map<std::string, std::string> fieldValues;
        for (const auto& field: IndexerBenchmarkDescription::getFieldNames()) {
            fieldValues.insert({field, ptree.get<std::string>(field)});
        }
        IndexerBenchmarkDescriptionPtr benchmarkDescriptionPtr = std::make_shared<IndexerBenchmarkDescription>();
        benchmarkDescriptionPtr->setPropertiesValues(fieldValues);
        return benchmarkDescriptionPtr;
    }

    BenchmarkDescriptionPtr BenchmarkDescriptionFactory::fromPtree(const boost::property_tree::ptree &ptree) {
        BenchmarkType type = fromString(ptree.get<std::string>(BenchmarkDescription::getTypeFieldName()));

        if (BenchmarkType::BSIFT == type) {
            return bsiftFactory.fromPtree(ptree);
        } else if (BenchmarkType::Indexer == type) {
            return indexerFactory.fromPtree(ptree);
        }

        return nullptr;
    }
}


