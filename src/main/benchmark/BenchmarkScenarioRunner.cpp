//
// Created by Przemek Piórkowski on 19.05.2016.
//

#include "BenchmarkScenarioRunner.h"
#include <chrono>
#include <src/main/algorithm/indexer/inverted_file/InvertedFileIndexer.h>
#include <src/main/algorithm/indexer/cross_indexer/CrossIndexer.h>
#include <src/main/algorithm/indexer/binary_inverted_file/BinaryInvertedFileIndexer.h>
#include <src/main/algorithm/indexer/supporting_words_inverted_file/SupportingWordsInvertedFileIndexer.h>
#include <src/main/retrieval/BagOfWords.h>
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
                             scenario->getIndexerBenchmarkDescriptions().size() +
                             scenario->getRetrievalBenchmarkDescriptions().size();

        BOOST_LOG_TRIVIAL(info) << "Faculty of Electronics Benchmark Scenario Runner";
        for (int i = 0; i < scenario->getBsiftBenchmarkDescriptions().size(); ++i) {
            BOOST_LOG_TRIVIAL(info) << "Running BSIFT benchmark " << ++globalTestCounter << " of " << allTestNumber;
            runBSIFTDescription(scenario->getBsiftBenchmarkDescriptions()[i]);
        }

        for (int i = 0; i < scenario->getIndexerBenchmarkDescriptions().size(); ++i) {
            BOOST_LOG_TRIVIAL(info) << "Running Indexer benchmark " << ++globalTestCounter << " of " << allTestNumber;
            runIndexerDescription(scenario->getIndexerBenchmarkDescriptions()[i]);
        }

        for (int i = 0; i < scenario->getRetrievalBenchmarkDescriptions().size(); ++i) {
            BOOST_LOG_TRIVIAL(info) << "Running Retrieval benchmark " << ++globalTestCounter << " of " << allTestNumber;
            runRetrievalDescription(scenario->getRetrievalBenchmarkDescriptions()[i]);
        }
    }

    void BenchmarkScenarioRunner::runBSIFTDescription(BSIFTBenchmarkPtr description) {
        BOOST_LOG_TRIVIAL(info) << "BSIFT benchmark " << description->getAlgorithm()->getBsiftMethod()->getMethod();
        std::vector<BSIFTBenchmarkSingleResult> resultVector;
        std::chrono::high_resolution_clock::time_point testStart;
        auto bsiftExtractor = buildExtractor(description->getAlgorithm());
        auto database = databaseFactory.createDatabase(description->getDatabasePath());

        if (description->isMeasureTime()) {
            testStart = std::chrono::high_resolution_clock::now();
        }

        database = bsiftExtractor->extractDatabaseBSIFT(database);

        if (description->isMeasureTime()) {
            std::chrono::high_resolution_clock::time_point testEnd = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(testEnd - testStart).count();
            BOOST_LOG_TRIVIAL(info) << description->getAlgorithm()->getBsiftMethod()->getMethod()
                                    << " extraction time: " << duration;
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

    void BenchmarkScenarioRunner::writeBSIFTResult(const std::string &filename,
                                                   const std::vector<BSIFTBenchmarkSingleResult> &result) {
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
        // place for further optimizations - perform concatenation only once for A and B set.
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

    void BenchmarkScenarioRunner::runIndexerDescription(IndexerBenchmarkPtr description) {
        BOOST_LOG_TRIVIAL(info) << "Indexer benchmark " << description->getMethod()->getMethodName();
        std::vector<IndexerBenchmarkSingleResult> result;
        auto testDatabase = databaseFactory.createDatabase(description->getDatabasePath());
        auto extractor = buildExtractor(description->getBsiftAlgorithm());
        auto indexer = buildIndexer(description->getMethod(), extractor);
        auto vocabulary = buildVocabulary(description->getMethod()->getVocabularyType(),
                                          description->getMethod()->getVocabularyPath());
        long int descriptorNumber = 1;
        std::chrono::high_resolution_clock::time_point testStart;
        std::chrono::high_resolution_clock::time_point testEnd;

        for (auto const & img : *testDatabase) {
            testStart = std::chrono::high_resolution_clock::now();
            indexer->query(buildQuery(img, extractor, vocabulary, description->getMethod()->getMethodName()));
            testEnd = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(testEnd - testStart).count();
            result.emplace_back(descriptorNumber++, duration);
        }

        writeIndexerResult(description->getResultFile(), result);
    }

    void BenchmarkScenarioRunner::writeIndexerResult(const std::string &filename,
                                                     const std::vector<IndexerBenchmarkSingleResult> &result) {
        std::ofstream resultFile;
        resultFile.open(filename);
        resultFile << "descriptorNo,time" << std::endl;
        for (const auto& r : result) {
            resultFile << r.first << "," << r.second << std::endl;
        }
        resultFile.close();
    }

    void BenchmarkScenarioRunner::runRetrievalDescription(RetrievalBenchmarkPtr description) {
        BOOST_LOG_TRIVIAL(info) << "Extractor: " << description->getBsiftAlgorithm()->getBsiftMethod()->getMethod();
        BOOST_LOG_TRIVIAL(info) << "Indexer  : " << description->getIndexerMethod()->getMethodName();
        BOOST_LOG_TRIVIAL(info) << "TestDB   : " << description->getTestDatabasePath();

        auto queryDatabase = databaseFactory.createDatabase(description->getTestDatabasePath());
        BagOfWords bow(description);
        std::chrono::high_resolution_clock::time_point testStart;
        std::chrono::high_resolution_clock::time_point testEnd;
        std::vector<RetrievalBenchmarkSingleResult> results;


        for (const auto & img : *queryDatabase) {
            BOOST_LOG_TRIVIAL(debug) << "Processing query of image: " << img->getFileName();
            if (description->getTimeMeasure()) {
                testStart = std::chrono::high_resolution_clock::now();
            }

            auto rankedList = bow.query(img);

            if (description->getTimeMeasure()) {
                testEnd = std::chrono::high_resolution_clock::now();
            }

            BOOST_LOG_TRIVIAL(debug) << "RankedList[1]: " << rankedList.empty() ?
                                     "is EMPTY" : rankedList.top().first->getFileName();

            auto stats = bow.computeResult(img, queryDatabase->getImageCategory(img), rankedList);

            if (description->getTimeMeasure()) {
                results.emplace_back(stats, std::chrono::duration_cast<std::chrono::milliseconds>
                        (testEnd - testStart).count());
            } else {
                results.emplace_back(stats);
            }
        }
        writeRetrievalResult(description->getResultFile(), results);
    }

    void BenchmarkScenarioRunner::writeRetrievalResult(const std::string &filename,
                                                       const std::vector<ImageRetrievalResult> &result) {
        std::ofstream resultFile;
        float mAP = 0;
        resultFile.open(filename);
        resultFile << "precision,recall,average_precision,time" << std::endl;
        for (const auto& r : result) {
            resultFile << r.precision << ","
                       << r.recall << ","
                       << r.averagePrecision << ","
                       << r.duration << std::endl;
            mAP += r.averagePrecision;
        }

        mAP /= static_cast<float>(result.size());

        BOOST_LOG_TRIVIAL(info) << "mAP: " << mAP;
        BOOST_LOG_TRIVIAL(info) << result.size() << " results saved in file " << filename;

        resultFile.close();
    }

}

