//
// Created by Przemek Piórkowski on 19.05.2016.
//

#ifndef FEITIR_BENCHMARKSCENARIORUNNER_H
#define FEITIR_BENCHMARKSCENARIORUNNER_H

#include "BenchmarkScenario.h"

namespace feitir {
    class BenchmarkScenarioRunner {
    public:
        BenchmarkScenarioRunner() = default;
        ~BenchmarkScenarioRunner() = default;
        void runScenario(BenchmarkScenario& scenario);
    };
}


#endif //FEITIR_BENCHMARKSCENARIORUNNER_H
