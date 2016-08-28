//
// Created by Przemek Piórkowski on 19.05.2016.
//

#ifndef FEITIR_BENCHMARKSCENARIORUNNER_H
#define FEITIR_BENCHMARKSCENARIORUNNER_H

#define BOOST_LOG_DYN_LINK 1

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <src/main/retrieval/BagOfWords.h>
#include "src/main/algorithm/BSIFT/BSIFTExtractor.h"
#include "src/main/algorithm/vocabulary/hierarchical_kmeans/HKMeansVocabularyBuilder.h"
#include "src/main/algorithm/vocabulary/kmeans/KMeansVocabularyBuilder.h"
#include "src/main/database/DatabaseFactory.h"
#include "src/main/benchmark/benchmark_description/bsift/BSIFTBenchmark.h"
#include "src/main/benchmark/benchmark_description/indexer/IndexerBenchmark.h"
#include "src/main/benchmark/benchmark_description/BenchmarkScenario.h"

namespace feitir {


    struct ImageRetrievalResult {
        const long long int duration;
        const float precision;
        const float recall;
        const float averagePrecision;

        ImageRetrievalResult(long long int duration, float precision,
                             float recall, float averagePrecision) : duration{duration},
                                                                     precision{precision},
                                                                     recall{recall},
                                                                     averagePrecision{averagePrecision} { }

        ImageRetrievalResult(BOWStats bowRes,
                             long long int duration = 0) : duration{duration},
                                                           precision{bowRes.precision},
                                                           recall{bowRes.recall},
                                                           averagePrecision{bowRes.avgPrecision} { }
    };

    class BenchmarkScenarioRunner {
    public:
        BenchmarkScenarioRunner() {
            boost::log::core::get()->set_filter(boost::log::trivial::severity >= boost::log::trivial::debug);
        };

        ~BenchmarkScenarioRunner() = default;
        void runScenario(BenchmarkScenarioPtr scenario);

    private:
        using BSIFTBenchmarkSingleResult = std::pair<float, int>;
        using IndexerBenchmarkSingleResult = std::pair<long int, long long int>;
        using RetrievalBenchmarkSingleResult = ImageRetrievalResult;
        using DescriptorPair = std::pair<cv::Mat, ImageBSIFT::BSIFT>;

        void runBSIFTDescription(BSIFTBenchmarkPtr description);
        void runIndexerDescription(IndexerBenchmarkPtr description);
        void runRetrievalDescription(RetrievalBenchmarkPtr description);

        std::vector<DescriptorPair> getDescriptorVector(const DatabasePtr database,
                                                        const std::vector<JSONObject::number> ids);
        std::vector<ImageBSIFT::BSIFT> concatenateBSIFT(const DatabasePtr database);
        cv::Mat concatenateSIFT(const DatabasePtr database);

        void writeBSIFTResult(const std::string& filename, const std::vector<BSIFTBenchmarkSingleResult>& result);
        void writeIndexerResult(const std::string& filename, const std::vector<IndexerBenchmarkSingleResult>& result);
        void writeRetrievalResult(const std::string& filename, const std::vector<RetrievalBenchmarkSingleResult>& result);

        DatabaseFactory databaseFactory;
        KMeansVocabularyBuilder kMeansVocabularyBuilder;
        HKMeansVocabularyBuilder hkMeansVocabularyBuilder;
    };
}


#endif //FEITIR_BENCHMARKSCENARIORUNNER_H
