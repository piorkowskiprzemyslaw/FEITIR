//
// Created by Przemek Piórkowski on 19.05.2016.
//

#include "BenchmarkScenarioRunner.h"
#include <chrono>
#include "src/main/algorithm/BSIFT/descriptor_median/DescriptorMedianBSIFTExtractor.h"
#include "src/main/algorithm/BSIFT/locality_sensitive_hashing/LocalitySensitiveHashingBSIFTExtractor.h"
#include "src/main/algorithm/BSIFT/vectors_compare/VectorsCompareBSIFTExtractor.h"
#include "src/main/algorithm/BSIFT/descriptor_voronoi_position/DescriptorVoronoiPositionBSIFTExtractor.h"
#include "src/main/algorithm/BSIFT/descriptor_position_median/DescriptorPositionMedianBSIFTExtractor.h"
#include "src/main/algorithm/BSIFT/comparison_array/ComparisonArrayBSIFTExtractor.h"

namespace feitir {
    void BenchmarkScenarioRunner::runScenario(BenchmarkScenarioPtr scenario) {
        int globalTestCounter = 0;
        auto allTestNumber = scenario->getBsiftBenchmarkDescriptions().size() +
                             scenario->getIndexerBenchmarkDescriptions().size();

        BOOST_LOG_TRIVIAL(info) << "Faculty of Electronics Benchmark Scenario Runner";
        for (int i = 0; i < scenario->getBsiftBenchmarkDescriptions().size(); ++i) {
            BOOST_LOG_TRIVIAL(info) << "Running BSIFT benchmark " << ++globalTestCounter << " of " << allTestNumber;
            runBSIFTDescription(scenario->getBsiftBenchmarkDescriptions()[i]);
        }

        for (int i = 0; i < scenario->getIndexerBenchmarkDescriptions().size(); ++i) {
            BOOST_LOG_TRIVIAL(info) << "Running Indexer benchmark " << ++globalTestCounter << " of " << allTestNumber;
            runIndexerDescription(scenario->getIndexerBenchmarkDescriptions()[i]);
        }
    }

    void BenchmarkScenarioRunner::runBSIFTDescription(BSIFTBenchmarkPtr description) {
        BOOST_LOG_TRIVIAL(info) << "BSIFT benchmark " + description->getAlgorithm()->getBsiftMethod()->getMethod();
        std::vector<SingleResult> resultVector;
        std::chrono::high_resolution_clock::time_point testStart;
        auto bsiftExtractor = setupExtractor(description->getAlgorithm());
        auto database = databaseFactory.createDatabase(description->getDatabasePath());

        if (description->isMeasureTime()) {
            testStart = std::chrono::high_resolution_clock::now();
        }

        database = bsiftExtractor->extractDatabaseBSIFT(database);

        if (description->isMeasureTime()) {
            std::chrono::high_resolution_clock::time_point testEnd = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(testEnd - testStart).count();
            BOOST_LOG_TRIVIAL(info) << description->getAlgorithm()->getBsiftMethod()->getMethod()
                                       + " extraction time: " << duration;
        }

        auto aSet = getDescriptorVector(database, description->getASet());
        auto bSet = getDescriptorVector(database, description->getBSet());

        for (const auto& aImg : aSet) {
            for (const auto& bImg : bSet) {
                resultVector.push_back({Util::euclideanDistanceVector(aImg.first, bImg.first)[0],
                                        Util::hammingDistance(aImg.second, bImg.second)});

            }
        }

        writeBSIFTResult(description->getResultFile(), resultVector);
    }

    void BenchmarkScenarioRunner::runIndexerDescription(IndexerBenchmarkPtr description) {
        BOOST_LOG_TRIVIAL(info) << "Indexer benchmark";
        auto database = databaseFactory.createDatabase(description->getDatabasePath());
        auto extractor = setupExtractor(description->getBsiftAlgorithm());
    }

    VocabularyTypePtr BenchmarkScenarioRunner::setupVocabulary(std::string vocabularyType, std::string vocabularyPath) {
        if (!vocabularyType.compare("kmeans")) {
            return kMeansVocabularyBuilder.readFromFile(vocabularyPath);
        } else if (!vocabularyType.compare("hkmeans")) {
            return hkMeansVocabularyBuilder.readFromFile(vocabularyPath);
        }
        throw std::invalid_argument(vocabularyType + " has no meaning as vocabulary type");
    }

    BSIFTExtractorPtr BenchmarkScenarioRunner::setupExtractor(BSIFTAlgorithmPtr algorithm) {
        auto database = databaseFactory.createDatabase(algorithm->getDatabasePath());
        auto vocabulary = setupVocabulary(algorithm->getVocabularyType(), algorithm->getVocabularyPath());
        return setupExtractor(algorithm->getBsiftMethod(), database, vocabulary);
    }

    BSIFTExtractorPtr BenchmarkScenarioRunner::setupExtractor(BSIFTMethodPtr method, DatabasePtr database,
                                                              VocabularyTypePtr vocabularyTypePtr) {
        std::string methodName = method->getMethod();
        if (!methodName.compare("comparison_array")) {
            return std::make_shared<ComparisonArrayBSIFTExtractor<>>(method->getN(), method->getL(), method->getT());
        } else if (!methodName.compare("descriptor_median")) {
            return std::make_shared<DescriptorMedianBSIFTExtractor>();
        } else if (!methodName.compare("descriptor_position_median")) {
            return std::make_shared<DescriptorPositionMedianBSIFTExtractor>();
        } else if (!methodName.compare("descriptor_voronoi_position")) {
            return std::make_shared<DescriptorVoronoiPositionBSIFTExtractor>(
                    method->getN(), vocabularyTypePtr, database);
        } else if (!methodName.compare("locality_sensitive_hashing")) {
            auto hashFunctions = LocalitySensitiveHashingBSIFTExtractor::generateRandomHashFunctions(method->getN());
            return std::make_shared<LocalitySensitiveHashingBSIFTExtractor>(method->getN(), hashFunctions);
        } else if (!methodName.compare("vectors_compare")) {
            return std::make_shared<VectorsCompareBSIFTExtractor>();
        }

        throw std::invalid_argument(methodName + " has no meaning as bsift extractor method");
    }

    void BenchmarkScenarioRunner::writeBSIFTResult(const std::string &filename,
                                                   const std::vector<SingleResult> &result) {
        std::ofstream resultFile;
        resultFile.open(filename);
        resultFile << "dsift,dbsift" << std::endl;
        for (const auto& r : result) {
            resultFile << r.first << "," << r.second << std::endl;
        }
        resultFile.close();
    }

    std::vector<BenchmarkScenarioRunner::DescriptorPair>
        BenchmarkScenarioRunner::getDescriptorVector(const DatabasePtr database,
                                                     const std::vector<JSONObject::number> ids) {
        std::vector<BenchmarkScenarioRunner::DescriptorPair> retVec;
        retVec.reserve(ids.size());
        // place for futher optimizations - perform concatenation only once for A and B set.
        std::vector<ImageBSIFT::BSIFT> concatenatedBSIFT = concatenateBSIFT(database);
        cv::Mat concatenatedSIFT = concatenateSIFT(database);

        // ensure that we are working on non empty BSIFT and SIFT descriptors sets.
        assert (concatenatedBSIFT.size() > 0 && concatenatedBSIFT.size() == concatenatedSIFT.rows);

        for (auto id : ids) {
            retVec.push_back({concatenatedSIFT.row(id), concatenatedBSIFT.at(id)});
        }

        return retVec;
    }

    std::vector<ImageBSIFT::BSIFT> BenchmarkScenarioRunner::concatenateBSIFT(const DatabasePtr database) {
        std::vector<ImageBSIFT::BSIFT> concatenated;
        for (auto img : *database) {
            auto imgBSIFT = std::dynamic_pointer_cast<ImageBSIFT>(img);
            assert (imgBSIFT != nullptr);
            for (auto bsift : imgBSIFT->getBsift()) {
                concatenated.push_back(bsift);
            }
        }
        return concatenated;
    }

    cv::Mat BenchmarkScenarioRunner::concatenateSIFT(const DatabasePtr database) {
        cv::Mat concatenated;
        for (auto img : *database) {
            concatenated.push_back(img->getDescriptors());
        }
        return concatenated;
    }

    MatchingFunc BenchmarkScenarioRunner::setupMatchingFunction(const std::string &matchingFunctionType,
                                                                const DatabasePtr database,
                                                                const VocabularyTypePtr vocabulary) {
        return feitir::MatchingFunc();
    }

}

