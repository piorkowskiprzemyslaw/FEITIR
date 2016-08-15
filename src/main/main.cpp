#include <iostream>
#include <sstream>
#include <fstream>
#include <boost/program_options.hpp>
#include "src/main/algorithm/vocabulary/kmeans/KMeansVocabularyBuilder.h"
#include "src/main/algorithm/vocabulary/hierarchical_kmeans/HKMeansVocabularyBuilder.h"
#include "src/main/benchmark/BenchmarkScenarioRunner.h"
#include "feitir_config.h"

namespace po = boost::program_options;
using namespace feitir;

inline std::string vocabularyDefaultFile() {
    auto t = std::time(nullptr);
    auto tm = *std::localtime(&t);
    std::stringstream stringstream;
    stringstream << std::put_time(&tm, "%H_%M_%S_%d_%m_%Y");
    std::string result;
    stringstream >> result;
    return "vocabulary_" + result + ".yml";
}

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
                 "file with json based benchmark scenario description")
                ("vKM", "create new kmeans vocabulary")
                ("vHKM", "create new hierarchical kmeans vocabulary")
                ("vocabularyK", po::value<int>()->default_value(2), "vocabulary K param")
                ("vocabularyL", po::value<int>()->default_value(1), "vocabulary L param")
                ("vocabularyFile", po::value<std::string>()->default_value(vocabularyDefaultFile()),
                 "filename to save vocabulary, by default vocabulary<current_timestamp>.yml")
                ("vocabularyDB", po::value<std::string>(),
                 "location of database which will be used to create vocabulary");

        po::variables_map variablesMap;
        po::store(po::command_line_parser(ac, av).options(commandLineOptions).run(), variablesMap);
        po::notify(variablesMap);

        if (variablesMap.count("help")) {
            std::cout << commandLineOptions << "\n";
            return 0;
        }

        if ((variablesMap.count("vKM") || variablesMap.count("vHKM")) && variablesMap.count("vocabularyDB")) {
            auto database = DatabaseFactory().createDatabase(variablesMap["vocabularyDB"].as<std::string>());
            if (variablesMap.count("vKM")) {
                KMeansVocabularyBuilder builder;
                auto vocabulary = builder.build(std::make_shared<KMeansParameter>(
                        database, variablesMap["vocabularyK"].as<int>()));
                builder.saveToFile(vocabulary, variablesMap["vocabularyFile"].as<std::string>());
            } else if (variablesMap.count("vHKM")) {
                HKMeansVocabularyBuilder builder;
                auto vocabulary = builder.build(std::make_shared<HKMeansParameter>(
                        database, variablesMap["vocabularyK"].as<int>(), variablesMap["vocabularyL"].as<int>()));
                builder.saveToFile(vocabulary, variablesMap["vocabularyFile"].as<std::string>());
            }
        } else {
            BenchmarkScenarioRunner runner;
            runner.runScenario(getJSONRootObjectFromFile<BenchmarkScenario>(benchmarkScenarioFile, "scenario"));
        }
    } catch(std::exception& e) {
        std::cout << e.what() << "\n";
    }

    return 0;
}
