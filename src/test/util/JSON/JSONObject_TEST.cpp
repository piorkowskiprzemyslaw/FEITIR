//
// Created by przemek on 23.05.16.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE FEITR_JSONObject test

#include <iostream>
#include "test_global.h"
#include <boost/test/unit_test.hpp>
#include "src/main/benchmark/BenchmarkScenario.h"

using namespace feitir;

struct JSONObjectFixture {
    const std::string resourcePath;
    const std::string sampleFile1;
    const std::string sampleFile2;
    const std::string sampleFile3;
    const std::string sampleFile4;
    const std::string rootObjectName;
    const std::vector<unsigned> aSet;
    const std::vector<unsigned> bSet;

    JSONObjectFixture() : resourcePath{resourcesRootDir() + "util/JSON/"},
                          sampleFile1{"sample1.json"},
                          sampleFile2{"sample2.json"},
                          sampleFile3{"sample3.json"},
                          sampleFile4{"sample4.json"},
                          rootObjectName{"scenario"},
                          aSet{38, 62, 12, 59, 4},
                          bSet{9, 87, 64, 53, 84, 13} { }
};

BOOST_FIXTURE_TEST_SUITE(JSONObject_TEST, JSONObjectFixture)

    BOOST_AUTO_TEST_CASE(Sample1JSONTest)
    {
        auto scenario = getJSONRootObjectFromFile<BenchmarkScenario>(resourcePath + sampleFile1, rootObjectName);
        BOOST_REQUIRE(scenario != nullptr);

        BOOST_REQUIRE_EQUAL(scenario->getBsiftBenchmarkDescriptions().size(), 1);
        auto bsiftDescription = scenario->getBsiftBenchmarkDescriptions()[0];
        BOOST_REQUIRE(bsiftDescription != nullptr);
        BOOST_REQUIRE_EQUAL(bsiftDescription->getDatabasePath(), "database_path");
        BOOST_REQUIRE_EQUAL(bsiftDescription->getResultFile(), "result_file");
        BOOST_REQUIRE_EQUAL_COLLECTIONS(bsiftDescription->getASet().begin(), bsiftDescription->getASet().end(),
                aSet.begin(), aSet.end());
        BOOST_REQUIRE_EQUAL_COLLECTIONS(bsiftDescription->getBSet().begin(), bsiftDescription->getBSet().end(),
                bSet.begin(), bSet.end());
        BOOST_REQUIRE(!bsiftDescription->isMeasureTime());
        auto algorithm = bsiftDescription->getAlgorithm();
        BOOST_REQUIRE(algorithm != nullptr);
        BOOST_REQUIRE_EQUAL(algorithm->getDatabasePath(), "algorithm_database_path");
        BOOST_REQUIRE_EQUAL(algorithm->getVocabularyType(), "algorithm_vocabulary_type");
        BOOST_REQUIRE_EQUAL(algorithm->getVocabularyPath(), "algorithm_vocabulary_path");

        auto bsiftMethod = algorithm->getBsiftMethod();
        BOOST_REQUIRE(bsiftMethod != nullptr);
        BOOST_REQUIRE_EQUAL(bsiftMethod->getMethod(), "method");
        BOOST_REQUIRE_EQUAL(bsiftMethod->getL(), 1);
        BOOST_REQUIRE_EQUAL(bsiftMethod->getT(), 2);
        BOOST_REQUIRE_EQUAL(bsiftMethod->getN(), 3);

        BOOST_REQUIRE_EQUAL(scenario->getIndexerBenchmarkDescriptions().size(), 1);
        auto indexerDescription = scenario->getIndexerBenchmarkDescriptions()[0];
        BOOST_REQUIRE(indexerDescription != nullptr);
        BOOST_REQUIRE_EQUAL(indexerDescription->getDatabasePath(), "database_path");
        BOOST_REQUIRE_EQUAL(indexerDescription->getResultFile(), "result_file");

        auto indexerMethod = indexerDescription->getMethod();
        BOOST_REQUIRE(indexerMethod != nullptr);
        BOOST_REQUIRE_EQUAL(indexerMethod->getMethodName(), "indexer_method");
        BOOST_REQUIRE_EQUAL(indexerMethod->getVocabularyPath(), "method_vocabulary_path");
        BOOST_REQUIRE_EQUAL(indexerMethod->getVocabularyType(), "method_vocabulary_type");
        BOOST_REQUIRE_EQUAL(indexerMethod->getMatchingFunc(), "matching_func");
        BOOST_REQUIRE_EQUAL(indexerMethod->getDatabasePath(), "method_database_path");
        BOOST_REQUIRE_EQUAL(indexerMethod->getThreshold(), 4);
        BOOST_REQUIRE_EQUAL(indexerMethod->getK(), 5);
        BOOST_REQUIRE_EQUAL(indexerMethod->getN(), 6);
        BOOST_REQUIRE_EQUAL(indexerMethod->getR(), 7);
        BOOST_REQUIRE_EQUAL(indexerMethod->getP(), 12);
        BOOST_REQUIRE_EQUAL(indexerMethod->getCodeWordSize(), 8);

        auto bsiftAlgorithm = indexerDescription->getBsiftAlgorithm();
        BOOST_REQUIRE(bsiftAlgorithm != nullptr);
        BOOST_REQUIRE_EQUAL(bsiftAlgorithm->getDatabasePath(), "algorithm_database_path");
        BOOST_REQUIRE_EQUAL(bsiftAlgorithm->getVocabularyPath(), "algorithm_vocabulary_path");
        BOOST_REQUIRE_EQUAL(bsiftAlgorithm->getVocabularyType(), "algorithm_vocabulary_type");

        bsiftMethod = bsiftAlgorithm->getBsiftMethod();
        BOOST_REQUIRE(bsiftMethod != nullptr);
        BOOST_REQUIRE_EQUAL(bsiftMethod->getMethod(), "algorithm_method");
        BOOST_REQUIRE_EQUAL(bsiftMethod->getL(), 9);
        BOOST_REQUIRE_EQUAL(bsiftMethod->getT(), 10);
        BOOST_REQUIRE_EQUAL(bsiftMethod->getN(), 11);
    }

    BOOST_AUTO_TEST_CASE(Sample2JSONTest)
    {
        auto scenario = getJSONRootObjectFromFile<BenchmarkScenario>(resourcePath + sampleFile2, rootObjectName);
        BOOST_REQUIRE(scenario != nullptr);

        BOOST_REQUIRE_EQUAL(scenario->getBsiftBenchmarkDescriptions().size(), 1);
        auto bsiftDescription = scenario->getBsiftBenchmarkDescriptions()[0];
        BOOST_REQUIRE(bsiftDescription != nullptr);
        BOOST_REQUIRE_EQUAL(bsiftDescription->getDatabasePath(), "database_path");
        BOOST_REQUIRE_EQUAL(bsiftDescription->getResultFile(), "result_file");
        BOOST_REQUIRE_EQUAL_COLLECTIONS(bsiftDescription->getASet().begin(), bsiftDescription->getASet().end(),
                aSet.begin(), aSet.end());
        BOOST_REQUIRE_EQUAL_COLLECTIONS(bsiftDescription->getBSet().begin(), bsiftDescription->getBSet().end(),
                bSet.begin(), bSet.end());
        BOOST_REQUIRE(!bsiftDescription->isMeasureTime());
        auto algorithm = bsiftDescription->getAlgorithm();
        BOOST_REQUIRE(algorithm != nullptr);
        BOOST_REQUIRE_EQUAL(algorithm->getDatabasePath(), "algorithm_database_path");
        BOOST_REQUIRE_EQUAL(algorithm->getVocabularyType(), "algorithm_vocabulary_type");
        BOOST_REQUIRE_EQUAL(algorithm->getVocabularyPath(), "algorithm_vocabulary_path");

        auto bsiftMethod = algorithm->getBsiftMethod();
        BOOST_REQUIRE(bsiftMethod != nullptr);
        BOOST_REQUIRE_EQUAL(bsiftMethod->getMethod(), "method");
        BOOST_REQUIRE_EQUAL(bsiftMethod->getL(), 1);
        BOOST_REQUIRE_EQUAL(bsiftMethod->getT(), 2);
        BOOST_REQUIRE_EQUAL(bsiftMethod->getN(), 3);

        BOOST_REQUIRE_EQUAL(scenario->getIndexerBenchmarkDescriptions().size(), 0);
    }

    BOOST_AUTO_TEST_CASE(Sample3JSONTest)
    {
        auto scenario = getJSONRootObjectFromFile<BenchmarkScenario>(resourcePath + sampleFile3, rootObjectName);
        BOOST_REQUIRE(scenario != nullptr);

        BOOST_REQUIRE_EQUAL(scenario->getBsiftBenchmarkDescriptions().size(), 0);

        auto indexerDescription = scenario->getIndexerBenchmarkDescriptions()[0];
        BOOST_REQUIRE(indexerDescription != nullptr);
        BOOST_REQUIRE_EQUAL(indexerDescription->getDatabasePath(), "database_path");
        BOOST_REQUIRE_EQUAL(indexerDescription->getResultFile(), "result_file");

        auto indexerMethod = indexerDescription->getMethod();
        BOOST_REQUIRE(indexerMethod != nullptr);
        BOOST_REQUIRE_EQUAL(indexerMethod->getMethodName(), "indexer_method");
        BOOST_REQUIRE_EQUAL(indexerMethod->getVocabularyPath(), "method_vocabulary_path");
        BOOST_REQUIRE_EQUAL(indexerMethod->getVocabularyType(), "method_vocabulary_type");
        BOOST_REQUIRE_EQUAL(indexerMethod->getMatchingFunc(), "matching_func");
        BOOST_REQUIRE_EQUAL(indexerMethod->getDatabasePath(), "method_database_path");
        BOOST_REQUIRE_EQUAL(indexerMethod->getThreshold(), 4);
        BOOST_REQUIRE_EQUAL(indexerMethod->getK(), 5);
        BOOST_REQUIRE_EQUAL(indexerMethod->getN(), 6);
        BOOST_REQUIRE_EQUAL(indexerMethod->getR(), 7);
        BOOST_REQUIRE_EQUAL(indexerMethod->getP(), 12);
        BOOST_REQUIRE_EQUAL(indexerMethod->getCodeWordSize(), 8);

        auto bsiftAlgorithm = indexerDescription->getBsiftAlgorithm();
        BOOST_REQUIRE(bsiftAlgorithm != nullptr);
        BOOST_REQUIRE_EQUAL(bsiftAlgorithm->getDatabasePath(), "algorithm_database_path");
        BOOST_REQUIRE_EQUAL(bsiftAlgorithm->getVocabularyPath(), "algorithm_vocabulary_path");
        BOOST_REQUIRE_EQUAL(bsiftAlgorithm->getVocabularyType(), "algorithm_vocabulary_type");

        auto bsiftMethod = bsiftAlgorithm->getBsiftMethod();
        BOOST_REQUIRE(bsiftMethod != nullptr);
        BOOST_REQUIRE_EQUAL(bsiftMethod->getMethod(), "algorithm_method");
        BOOST_REQUIRE_EQUAL(bsiftMethod->getL(), 9);
        BOOST_REQUIRE_EQUAL(bsiftMethod->getT(), 10);
        BOOST_REQUIRE_EQUAL(bsiftMethod->getN(), 11);
    }

    BOOST_AUTO_TEST_CASE(Sample4JSONTest)
    {
        auto scenario = getJSONRootObjectFromFile<BenchmarkScenario>(resourcePath + sampleFile4, rootObjectName);
        BOOST_REQUIRE(scenario != nullptr);

        BOOST_REQUIRE_EQUAL(scenario->getBsiftBenchmarkDescriptions().size(), 0);
        BOOST_REQUIRE_EQUAL(scenario->getIndexerBenchmarkDescriptions().size(), 0);
    }

    BOOST_AUTO_TEST_CASE(MissingObjectJSONTest)
    {
        auto scenario = getJSONRootObjectFromFile<BenchmarkScenario>(resourcePath + sampleFile1, "aaaa");
        BOOST_REQUIRE(scenario == nullptr);
    }

BOOST_AUTO_TEST_SUITE_END()