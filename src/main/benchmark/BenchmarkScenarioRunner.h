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
#include "src/main/benchmark/benchmark_description/bsift/BSIFTBenchmark.h"
#include "src/main/benchmark/benchmark_description/indexer/IndexerBenchmark.h"
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
        using SingleResult = std::pair<float, int>;
        using DescriptorPair = std::pair<cv::Mat, ImageBSIFT::BSIFT>;

        void runBSIFTDescription(BSIFTBenchmarkPtr description);
        void runIndexerDescription(IndexerBenchmarkPtr description);
        std::vector<DescriptorPair> getDescriptorVector(const DatabasePtr database,
                                                        const std::vector<JSONObject::number> ids);
        VocabularyTypePtr setupVocabulary(std::string vocabularyType, std::string vocabularyPath);

        BSIFTExtractorPtr setupExtractor(BSIFTAlgorithmPtr algorithm);
        BSIFTExtractorPtr setupExtractor(BSIFTMethodPtr method, DatabasePtr imageDatabase,
                                         VocabularyTypePtr vocabularyTypePtr);

        void writeBSIFTResult(const std::string& filename, const std::vector<SingleResult>& result);
        std::vector<ImageBSIFT::BSIFT> concatenateBSIFT(const DatabasePtr database);
        cv::Mat concatenateSIFT(const DatabasePtr database);

        IndexerPtr setupIndexer(const IndexerMethodPtr indexerMethod);

        MatchingFunc setupMatchingFunction(const std::string &matchingFunctionType, const DatabasePtr database,
                                           const VocabularyTypePtr vocabulary);

        DatabaseFactory databaseFactory;
        KMeansVocabularyBuilder kMeansVocabularyBuilder;
        HKMeansVocabularyBuilder hkMeansVocabularyBuilder;
    };
}


#endif //FEITIR_BENCHMARKSCENARIORUNNER_H
