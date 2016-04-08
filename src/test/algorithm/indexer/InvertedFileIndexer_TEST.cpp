//
// Created by Przemek Piórkowski on 04.04.2016.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE FEITR_InvertedFileIndexer_test

#include <iostream>
#include "test_global.h"
#include <boost/test/unit_test.hpp>
#include <src/main/database/DatabaseFactory.h>
#include <src/main/algorithm/indexer/inverted_file/InvertedFileIndexer.h>
#include <src/main/algorithm/vocabulary/kmeans/KMeansVocabularyBuilder.h>

using namespace feitir;

struct InvertedFileIndexerFixture {
    const std::string resourcePath;
    const std::string thirdRoot;
    const int means;
    DatabaseFactory databaseFactory;
    KMeansVocabularyBuilder vocabularyBuilder;


    InvertedFileIndexerFixture() : resourcePath{resourcesRootDir() + "database/"},
                                   thirdRoot{"dir3/"},
                                   means{10} {

    }
};

BOOST_FIXTURE_TEST_SUITE(InvertedFileIndexer_TEST, InvertedFileIndexerFixture)

    BOOST_AUTO_TEST_CASE(FirstTestCase)
    {
        auto database = databaseFactory.createDatabase(resourcePath + thirdRoot);
        auto kMeansParameters = std::make_shared<KMeansParameter>(database, means);

        unsigned sum = 0;
        for (auto& image : database->getImages()) {
            sum += image->getDescriptors().rows;
        }
        for (auto& cat : database->getCategories()) {
            for (auto& img : cat->getImages()) {
                sum += img->getDescriptors().rows;
            }
        }

        BOOST_REQUIRE_EQUAL(kMeansParameters->getData().rows, sum);
        auto vocabulary = vocabularyBuilder.build(std::make_shared<KMeansParameter>(database, means));
        InvertedFileIndexer indexer(std::make_shared<IFParameters>(database, vocabulary));

        BOOST_REQUIRE(true);
    }

BOOST_AUTO_TEST_SUITE_END()