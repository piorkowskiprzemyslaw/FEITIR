//
// Created by Przemek Piórkowski on 19.05.2016.
//

#define BOOST_LOG_DYN_LINK 1

#include "BenchmarkScenarioRunner.h"
#include <boost/log/trivial.hpp>
#include "src/main/algorithm/BSIFT/descriptor_median/DescriptorMedianBSIFTExtractor.h"
#include "src/main/algorithm/BSIFT/locality_sensitive_hashing/LocalitySensitiveHashingBSIFTExtractor.h"
#include "src/main/algorithm/BSIFT/vectors_compare/VectorsCompareBSIFTExtractor.h"
#include "src/main/algorithm/BSIFT/descriptor_voronoi_position/DescriptorVoronoiPositionBSIFTExtractor.h"
#include "src/main/algorithm/BSIFT/descriptor_position_median/DescriptorPositionMedianBSIFTExtractor.h"
#include "src/main/algorithm/BSIFT/comparison_array/ComparisonArrayBSIFTExtractor.h"


namespace feitir {
    void BenchmarkScenarioRunner::runScenario(const feitir::BenchmarkScenario &scenario) {
        BOOST_LOG_TRIVIAL(info) << "Faculty of Electronics Benchmark Scenario Runner";
        for (int i = 0; i < scenario.getDescriptions().size(); ++i) {
            BOOST_LOG_TRIVIAL(info) << "Running benchmark " << i + 1 << " of " << scenario.getDescriptions().size();
            runDescription(scenario.getDescriptions()[i]);
        }
    }

    void BenchmarkScenarioRunner::runDescription(const BenchmarkDescriptionPtr descriptionPtr) {
        if (nullptr != std::dynamic_pointer_cast<BSIFTBenchmarkDescription>(descriptionPtr)) {
            runBSIFTDescription(std::dynamic_pointer_cast<BSIFTBenchmarkDescription>(descriptionPtr));
        } else if (nullptr != std::dynamic_pointer_cast<IndexerBenchmarkDescription>(descriptionPtr)) {
            runIndexerDescription(std::dynamic_pointer_cast<IndexerBenchmarkDescription>(descriptionPtr));
        }
    }

    void BenchmarkScenarioRunner::runBSIFTDescription(const BSIFTBenchmarkDescriptionPtr descriptionPtr) {
        BOOST_LOG_TRIVIAL(info) << "BSIFT benchmark";
        auto database = databaseFactory.createDatabase(descriptionPtr->getDatabasePath());
        auto vocabulary = setupVocabulary(descriptionPtr->getVocabularyType(), descriptionPtr->getVocabularyPath());
        BSIFTDatabaseExtractorPtr bsiftExtractor = setupExtractor(descriptionPtr->getMethodDescription(),
                                                                  database, vocabulary);
        auto transformedDatabase = bsiftExtractor->extractDatabaseBSIFT(database);

        // TODO randomly choose one element, compute distance between choosen element and each database
        // descriptor in two ways - hamming distance and euclidean distance. wirte down results to result file.

    }

    void BenchmarkScenarioRunner::runIndexerDescription(const IndexerBenchmarkDescriptionPtr descriptionPtr) {
        BOOST_LOG_TRIVIAL(info) << "Indexer benchmark";
        auto database = databaseFactory.createDatabase(descriptionPtr->getDatabasePath());
        auto vocabulary = setupVocabulary(descriptionPtr->getVocabularyType(), descriptionPtr->getVocabularyPath());
    }

    VocabularyTypePtr BenchmarkScenarioRunner::setupVocabulary(std::string vocabularyType, std::string vocabularyPath) {
        if (!vocabularyType.compare("kmeans")) {
            return kMeansVocabularyBuilder.readFromFile(vocabularyPath);
        } else if (!vocabularyType.compare("hkmeans")) {
            return hkMeansVocabularyBuilder.readFromFile(vocabularyPath);
        }
        throw std::invalid_argument(vocabularyType + " has no meaning as vocabulary type");
    }

    BSIFTDatabaseExtractorPtr BenchmarkScenarioRunner::setupExtractor(BSIFTMethodDescription method,
                                                                      DatabasePtr database,
                                                                      VocabularyTypePtr vocabularyTypePtr) {
        std::string methodName = method.getMethod();
        if (!methodName.compare("comparison_array")) {
            return std::make_shared<ComparisonArrayBSIFTExtractor<CmpArrN()>>(method.getL(), method.getT());
        } else if (!methodName.compare("descriptor_median")) {
            return std::make_shared<DescriptorMedianBSIFTExtractor>();
        } else if (!methodName.compare("descriptor_position_median")) {
            return std::make_shared<DescriptorPositionMedianBSIFTExtractor>();
        } else if (!methodName.compare("descriptor_voronoi_position")) {
            return std::make_shared<DescriptorVoronoiPositionBSIFTExtractor<VorPosN()>>(vocabularyTypePtr, database);
        } else if (!methodName.compare("locality_sensitive_hashing")) {
            auto hashFunctions = LocalitySensitiveHashingBSIFTExtractor<LSHN()>::generateRandomHashFunctions();
            return std::make_shared<LocalitySensitiveHashingBSIFTExtractor<LSHN()>>(hashFunctions);
        } else if (!methodName.compare("vectors_compare")) {
            return std::make_shared<VectorsCompareBSIFTExtractor>();
        }

        throw std::invalid_argument(methodName + " has no meaning as bsift extractor method");
    }
}

