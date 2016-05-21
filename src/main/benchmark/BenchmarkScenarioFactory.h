//
// Created by Przemek Piórkowski on 21.05.2016.
//

#ifndef FEITIR_BENCHAMRKSCENARIOFACTORY_H
#define FEITIR_BENCHAMRKSCENARIOFACTORY_H

#include <iostream>
#include <string>
#include "BenchmarkScenario.h"
#include "src/main/benchmark/benchmark_description/BenchmarkDescriptionFactory.h"

namespace feitir {
    class BenchmarkScenarioFactory {
    public:
        BenchmarkScenario fromJSON(const std::string& fileName);

    protected:
        std::vector<BenchmarkDescriptionPtr> readDescriptions(
                boost::optional<boost::property_tree::ptree &> scenariosOptional);

    private:
        BenchmarkDescriptionFactory descriptionFactory;
    };
}


#endif //FEITIR_BENCHAMRKSCENARIOFACTORY_H
