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
        BOOST_LOG_TRIVIAL(info) << "Faculty of Electronics Benchmark Scenario Runner";
        for (int i = 0; i < scenario->getBsiftBenchmarkDescriptions().size(); ++i) {
            BOOST_LOG_TRIVIAL(info) << "Running BSIFT benchmark " << i + 1
                                    << " of " << scenario->getBsiftBenchmarkDescriptions().size();
            runBSIFTDescription(scenario->getBsiftBenchmarkDescriptions()[i]);
        }

        for (int i = 0; i < scenario->getIndexerBenchmarkDescriptions().size(); ++i) {
            BOOST_LOG_TRIVIAL(info) << "Running Indexer benchmark " << i + 1
                                    << " of " << scenario->getIndexerBenchmarkDescriptions().size();
            runIndexerDescription(scenario->getIndexerBenchmarkDescriptions()[i]);
        }
    }

    void BenchmarkScenarioRunner::runBSIFTDescription(BSIFTBenchmarkDescriptionPtr description) {
        BOOST_LOG_TRIVIAL(info) << "BSIFT benchmark " + description->getMethodDescription()->getMethod();
        std::vector<SingleBSFITResult> resultVector;
        std::chrono::high_resolution_clock::time_point t1;
        auto database = databaseFactory.createDatabase(description->getDatabasePath());
        auto vocabulary = setupVocabulary(description->getVocabularyType(), description->getVocabularyPath());
        BSIFTExtractorPtr bsiftExtractor = setupExtractor(description->getMethodDescription(), database, vocabulary);

        if (description->isMeasureTime()) {
            t1 = std::chrono::high_resolution_clock::now();
        }

        database = bsiftExtractor->extractDatabaseBSIFT(database);

        if (description->isMeasureTime()) {
            std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
            BOOST_LOG_TRIVIAL(info) << description->getMethodDescription()->getMethod() + " extraction time: " << duration;
        }

        auto referenceDescriptors = getFirstDescriptors(database);
        for (const auto& img : *database) {
            BOOST_LOG_TRIVIAL(debug) << "Processing image " << img->getFileName();
            auto originalVectorsDistances
                    = util.euclideanDistanceVector(img->getDescriptors(),
                                                   cv::repeat(referenceDescriptors.first,
                                                              img->getDescriptors().rows, 1));
            auto bsiftImg = std::dynamic_pointer_cast<ImageBSIFT>(img);
            assert (bsiftImg != nullptr);
            for (int i = 0; i < bsiftImg->getDescriptors().rows; ++i) {
                resultVector.push_back({originalVectorsDistances[i],
                                       util.hammingDistance(referenceDescriptors.second, bsiftImg->getBsift()[i])});
            }
        }

        writeBSIFTResult(description->getResultFile(), resultVector);
    }

    void BenchmarkScenarioRunner::runIndexerDescription(IndexerBenchmarkDescriptionPtr description) {
        BOOST_LOG_TRIVIAL(info) << "Indexer benchmark";
        auto database = databaseFactory.createDatabase(description->getDatabasePath());
        auto vocabulary = setupVocabulary(description->getVocabularyType(), description->getVocabularyPath());
    }

    VocabularyTypePtr BenchmarkScenarioRunner::setupVocabulary(std::string vocabularyType, std::string vocabularyPath) {
        if (!vocabularyType.compare("kmeans")) {
            return kMeansVocabularyBuilder.readFromFile(vocabularyPath);
        } else if (!vocabularyType.compare("hkmeans")) {
            return hkMeansVocabularyBuilder.readFromFile(vocabularyPath);
        }
        throw std::invalid_argument(vocabularyType + " has no meaning as vocabulary type");
    }

    BSIFTExtractorPtr BenchmarkScenarioRunner::setupExtractor(BSIFTMethodDescriptionPtr method, DatabasePtr database,
                                                              VocabularyTypePtr vocabularyTypePtr) {
        std::string methodName = method->getMethod();
        if (!methodName.compare("comparison_array")) {
            return std::make_shared<ComparisonArrayBSIFTExtractor<>>(method->getN(), method->getL(), method->getT());
        } else if (!methodName.compare("descriptor_median")) {
            return std::make_shared<DescriptorMedianBSIFTExtractor>();
        } else if (!methodName.compare("descriptor_position_median")) {
            return std::make_shared<DescriptorPositionMedianBSIFTExtractor>();
        } else if (!methodName.compare("descriptor_voronoi_position")) {
            return std::make_shared<DescriptorVoronoiPositionBSIFTExtractor>(method->getN(), vocabularyTypePtr, database);
        } else if (!methodName.compare("locality_sensitive_hashing")) {
            auto hashFunctions = LocalitySensitiveHashingBSIFTExtractor::generateRandomHashFunctions(method->getN());
            return std::make_shared<LocalitySensitiveHashingBSIFTExtractor>(method->getN(), hashFunctions);
        } else if (!methodName.compare("vectors_compare")) {
            return std::make_shared<VectorsCompareBSIFTExtractor>();
        }

        throw std::invalid_argument(methodName + " has no meaning as bsift extractor method");
    }

    std::pair<cv::Mat, ImageBSIFT::BSIFT> BenchmarkScenarioRunner::getFirstDescriptors(const DatabasePtr database) {
        auto begIt = database->begin();
        assert (begIt != database->end());
        auto bsiftImg = std::dynamic_pointer_cast<ImageBSIFT>(*begIt);
        assert (bsiftImg->getBsift().size() > 0 && bsiftImg->getDescriptors().rows > 0);
        assert (bsiftImg->getBsift().size() == bsiftImg->getDescriptors().rows);
        return std::make_pair(bsiftImg->getDescriptors().row(0), bsiftImg->getBsift()[0]);
    }

    void BenchmarkScenarioRunner::writeBSIFTResult(const std::string &filename,
                                                   const std::vector<SingleBSFITResult> &result) {
        std::ofstream resultFile;
        resultFile.open(filename);
        resultFile << "dsift,dbsift" << std::endl;
        for (const auto& r : result) {
            resultFile << r.first << "," << r.second << std::endl;
        }
        resultFile.close();
    }

}

