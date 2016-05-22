//
// Created by Przemek Piórkowski on 21.05.2016.
//

#include "BenchmarkDescriptionFactory.h"

namespace feitir {

    BSIFTBenchmarkDescriptionPtr BSIFTBenchmarkDescriptionFactory::fromPtree(const boost::property_tree::ptree &ptree) {
        std::map<std::string, std::string> fieldValues =
                BenchmarkDescriptionFactory::getFieldsValue(BSIFTBenchmarkDescription::getFieldNames(),ptree);

        std::map<std::string, std::map<std::string, std::string>> compoundFieldValues;
        for (const auto& field: BSIFTBenchmarkDescription::getCompoundFieldsNames()) {
            boost::optional<const boost::property_tree::ptree &> ptreeOptional = ptree.get_child_optional(field.first);
            if (ptreeOptional) {
                compoundFieldValues.insert({field.first,
                        BenchmarkDescriptionFactory::getFieldsValue(field.second, *ptreeOptional)});
            }
        }

        BSIFTBenchmarkDescriptionPtr benchmarkDescriptionPtr = std::make_shared<BSIFTBenchmarkDescription>();
        benchmarkDescriptionPtr->setBasicPropertiesValues(fieldValues);
        benchmarkDescriptionPtr->setCompoundPropertiesValues(compoundFieldValues);
        return benchmarkDescriptionPtr;
    }

    IndexerBenchmarkDescriptionPtr IndexerBenchmarkDescriptionFactory::fromPtree(const boost::property_tree::ptree &ptree) {
        std::map<std::string, std::string> fieldValues;
        for (const auto& field: IndexerBenchmarkDescription::getFieldNames()) {
            fieldValues.insert({field, ptree.get<std::string>(field)});
        }
        IndexerBenchmarkDescriptionPtr benchmarkDescriptionPtr = std::make_shared<IndexerBenchmarkDescription>();
        benchmarkDescriptionPtr->setBasicPropertiesValues(fieldValues);
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

    std::map<std::string, std::string> BenchmarkDescriptionFactory::getFieldsValue(
            const std::vector<std::string> &fieldNames, const boost::property_tree::ptree& ptree) {
        std::map<std::string, std::string> result;
        for (const auto& field: fieldNames) {
            result.insert({field, ptree.get<std::string>(field)});
        }
        return result;
    }

}


