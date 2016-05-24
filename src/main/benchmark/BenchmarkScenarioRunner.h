//
// Created by Przemek Piórkowski on 19.05.2016.
//

#ifndef FEITIR_BENCHMARKSCENARIORUNNER_H
#define FEITIR_BENCHMARKSCENARIORUNNER_H

#include "benchmark_config.h"
#include "src/main/algorithm/BSIFT/BSIFTExtractor.h"
#include "src/main/algorithm/vocabulary/hierarchical_kmeans/HKMeansVocabularyBuilder.h"
#include "src/main/algorithm/vocabulary/kmeans/KMeansVocabularyBuilder.h"
#include "src/main/database/DatabaseFactory.h"
#include "src/main/benchmark/benchmark_description/BSIFTBenchmarkDescription.h"
#include "src/main/benchmark/benchmark_description/IndexerBenchmarkDescription.h"
#include "BenchmarkScenario.h"

namespace feitir {
    class BenchmarkScenarioRunner {
    public:
        BenchmarkScenarioRunner() = default;
        ~BenchmarkScenarioRunner() = default;
        void runScenario(BenchmarkScenarioPtr scenario);

    private:
        void runBSIFTDescription(BSIFTBenchmarkDescriptionPtr description);
        void runIndexerDescription(IndexerBenchmarkDescriptionPtr description);
        VocabularyTypePtr setupVocabulary(std::string vocabularyType, std::string vocabularyPath);
        BSIFTDatabaseExtractorPtr setupExtractor(BSIFTMethodDescriptionPtr method,
                                                 DatabasePtr imageDatabase,
                                                 VocabularyTypePtr vocabularyTypePtr);

        DatabaseFactory databaseFactory;
        KMeansVocabularyBuilder kMeansVocabularyBuilder;
        HKMeansVocabularyBuilder hkMeansVocabularyBuilder;
    };
}


#endif //FEITIR_BENCHMARKSCENARIORUNNER_H
