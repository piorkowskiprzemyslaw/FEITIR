//
// Created by Przemek Piórkowski on 21.05.2016.
//

#include "BenchmarkDescription.h"

namespace feitir {
    BenchmarkType fromString(const std::string &str) {

        if (!str.compare("BSIFTBenchmark")) {
            return BenchmarkType::BSIFT;
        } else if (!str.compare("IndexerBenchmark")) {
            return BenchmarkType::Indexer;
        }

        throw new std::invalid_argument(str + " has no representation as enum of type BenchmarkType");
    }

    BenchmarkType BenchmarkDescription::getType() const {
        return type;
    }

    std::string BenchmarkDescription::getTypeFieldName() {
        return "type";
    }

}

