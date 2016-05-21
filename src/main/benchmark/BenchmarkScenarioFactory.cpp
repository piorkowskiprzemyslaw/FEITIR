//
// Created by Przemek Piórkowski on 21.05.2016.
//

#include "BenchmarkScenarioFactory.h"

using namespace boost::property_tree;
using namespace boost;

namespace feitir {
    BenchmarkScenario BenchmarkScenarioFactory::fromJSON(const std::string &fileName) {
        ptree propertyTree;
        read_json(fileName.c_str(), propertyTree);
        return BenchmarkScenario(readDescriptions(propertyTree.get_child_optional("scenarios")));
    }

    std::vector<BenchmarkDescriptionPtr> BenchmarkScenarioFactory::readDescriptions(optional<ptree &> scenariosOptional) {
        std::vector<BenchmarkDescriptionPtr> result;

        if (scenariosOptional) {
            for (const auto& description : *scenariosOptional) {
                BenchmarkDescriptionPtr scenarioDescription = descriptionFactory.fromPtree(description.second);
                if (nullptr != scenarioDescription) {
                    result.push_back(scenarioDescription);
                }
            }

        }

        return result;
    }


}
