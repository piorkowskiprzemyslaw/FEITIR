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
        void runScenario(const BenchmarkScenario& scenario);

    protected:
        void runDescription(const BenchmarkDescriptionPtr descriptionPtr);

    private:
        void runBSIFTDescription(const BSIFTBenchmarkDescriptionPtr descriptionPtr);
        void runIndexerDescription(const IndexerBenchmarkDescriptionPtr descriptionPtr);
        VocabularyTypePtr setupVocabulary(std::string vocabularyType, std::string vocabularyPath);
        BSIFTDatabaseExtractorPtr setupExtractor(BSIFTMethodDescription method, DatabasePtr imageDatabase,
                                                 VocabularyTypePtr vocabularyTypePtr);

        DatabaseFactory databaseFactory;
        KMeansVocabularyBuilder kMeansVocabularyBuilder;
        HKMeansVocabularyBuilder hkMeansVocabularyBuilder;
    };
}


#endif //FEITIR_BENCHMARKSCENARIORUNNER_H
