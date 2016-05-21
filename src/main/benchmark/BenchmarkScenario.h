//
// Created by Przemek Piórkowski on 19.05.2016.
//

#ifndef FEITIR_BENCHMARKSCENARIO_H
#define FEITIR_BENCHMARKSCENARIO_H

#include <iostream>
#include <boost/program_options.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "BenchmarkDescription.h"

namespace feitir {
    class BenchmarkScenario {
    public:
        BenchmarkScenario(std::vector<BenchmarkDescriptionPtr> descriptions);
        ~BenchmarkScenario() = default;
        const std::vector<BenchmarkDescriptionPtr> & getDescriptions() const;

    private:
        std::vector<BenchmarkDescriptionPtr> descriptions;
    };

}


#endif //FEITIR_BENCHMARKSCENARIO_H
