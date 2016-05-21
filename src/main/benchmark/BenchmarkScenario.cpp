//
// Created by Przemek Piórkowski on 19.05.2016.
//

#include "BenchmarkScenario.h"

namespace feitir {

    BenchmarkScenario::BenchmarkScenario(std::vector<BenchmarkDescriptionPtr> descriptions)
            : descriptions{std::move(descriptions)} { }

    const std::vector<BenchmarkDescriptionPtr> &BenchmarkScenario::getDescriptions() const {
        return descriptions;
    }

}