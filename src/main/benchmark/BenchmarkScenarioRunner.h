//
// Created by Przemek Piórkowski on 19.05.2016.
//

#ifndef FEITIR_BENCHMARKSCENARIORUNNER_H
#define FEITIR_BENCHMARKSCENARIORUNNER_H

#define BOOST_LOG_DYN_LINK 1

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
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
        BenchmarkScenarioRunner() {
            boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::info);
        };

        ~BenchmarkScenarioRunner() = default;
        void runScenario(BenchmarkScenarioPtr scenario);

    private:
        using SingleBSFITResult = std::pair<float, int>;

        void runBSIFTDescription(BSIFTBenchmarkDescriptionPtr description);
        void runIndexerDescription(IndexerBenchmarkDescriptionPtr description);
        std::pair<cv::Mat, ImageBSIFT::BSIFT> getFirstDescriptors(const DatabasePtr database);
        VocabularyTypePtr setupVocabulary(std::string vocabularyType, std::string vocabularyPath);
        BSIFTExtractorPtr setupExtractor(BSIFTMethodDescriptionPtr method,
                                         DatabasePtr imageDatabase,
                                         VocabularyTypePtr vocabularyTypePtr);
        void writeBSIFTResult(const std::string& filename, const std::vector<SingleBSFITResult>& result);

        DatabaseFactory databaseFactory;
        KMeansVocabularyBuilder kMeansVocabularyBuilder;
        HKMeansVocabularyBuilder hkMeansVocabularyBuilder;
    };
}


#endif //FEITIR_BENCHMARKSCENARIORUNNER_H
