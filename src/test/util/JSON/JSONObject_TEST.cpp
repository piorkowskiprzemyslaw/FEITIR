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

    JSONObjectFixture() : resourcePath{resourcesRootDir() + "util/JSON/"},
                          sampleFile1{"sample1.json"},
                          sampleFile2{"sample2.json"},
                          sampleFile3{"sample3.json"},
                          sampleFile4{"sample4.json"},
                          rootObjectName{"scenario"} { }
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
        BOOST_REQUIRE_EQUAL(bsiftDescription->getVocabularyPath(), "vocabulary_path");
        BOOST_REQUIRE_EQUAL(bsiftDescription->getVocabularyType(), "vocabulary_type");
        BOOST_REQUIRE(!bsiftDescription->isMeasureTime());
        auto bsiftMethod = bsiftDescription->getMethodDescription();
        BOOST_REQUIRE_EQUAL(bsiftMethod->getMethod(), "method");
        BOOST_REQUIRE_EQUAL(bsiftMethod->getL(), 1);
        BOOST_REQUIRE_EQUAL(bsiftMethod->getT(), 2);
        BOOST_REQUIRE_EQUAL(bsiftMethod->getN(), 3);

        BOOST_REQUIRE_EQUAL(scenario->getIndexerBenchmarkDescriptions().size(), 1);
        auto indexerDescription = scenario->getIndexerBenchmarkDescriptions()[0];
        BOOST_REQUIRE(indexerDescription != nullptr);
        BOOST_REQUIRE_EQUAL(indexerDescription->getDatabasePath(), "database_path");
        BOOST_REQUIRE_EQUAL(indexerDescription->getResultFile(), "result_file");
        BOOST_REQUIRE_EQUAL(indexerDescription->getVocabularyPath(), "vocabulary_path");
        BOOST_REQUIRE_EQUAL(indexerDescription->getVocabularyType(), "vocabulary_type");
        BOOST_REQUIRE_EQUAL(indexerDescription->getMethod(), "method");
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
        BOOST_REQUIRE_EQUAL(bsiftDescription->getVocabularyPath(), "vocabulary_path");
        BOOST_REQUIRE_EQUAL(bsiftDescription->getVocabularyType(), "vocabulary_type");
        BOOST_REQUIRE(!bsiftDescription->isMeasureTime());
        auto bsiftMethod = bsiftDescription->getMethodDescription();
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

        BOOST_REQUIRE_EQUAL(scenario->getIndexerBenchmarkDescriptions().size(), 1);
        auto indexerDescription = scenario->getIndexerBenchmarkDescriptions()[0];
        BOOST_REQUIRE(indexerDescription != nullptr);
        BOOST_REQUIRE_EQUAL(indexerDescription->getDatabasePath(), "database_path");
        BOOST_REQUIRE_EQUAL(indexerDescription->getResultFile(), "result_file");
        BOOST_REQUIRE_EQUAL(indexerDescription->getVocabularyPath(), "vocabulary_path");
        BOOST_REQUIRE_EQUAL(indexerDescription->getVocabularyType(), "vocabulary_type");
        BOOST_REQUIRE_EQUAL(indexerDescription->getMethod(), "method");
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