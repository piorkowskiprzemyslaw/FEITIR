#include <iostream>
#include <fstream>
#include <boost/program_options.hpp>
#include "src/main/benchmark/BenchmarkScenarioFactory.h"
#include "feitir_config.h"

namespace po = boost::program_options;
using namespace feitir;

inline std::string benchmarkDefaultFile() {
    boost::filesystem::path path(projectRootDir().c_str());
    path /= "benchmarkScenario.json";
    return path.string();
}

int main(int ac, char* av[]) {
    try {
        std::string benchmarkScenarioFile;
        po::options_description commandLineOptions("Faculty of Electronics and Information Technology Image Retrieval tool");
        commandLineOptions.add_options()
                ("help", "produce help message")
                ("benchmarkScenario,b", po::value<std::string>(&benchmarkScenarioFile)
                        ->default_value(benchmarkDefaultFile()),
                 "file with json based benchmark scenario description");

        po::variables_map variablesMap;
        po::store(po::command_line_parser(ac, av).options(commandLineOptions).run(), variablesMap);
        po::notify(variablesMap);

        if (variablesMap.count("help")) {
            std::cout << commandLineOptions << "\n";
            return 0;
        }

        BenchmarkScenario scenario = BenchmarkScenarioFactory().fromJSON(benchmarkScenarioFile);

    } catch(std::exception& e) {
        std::cout << e.what() << "\n";
    }

    return 0;
}
