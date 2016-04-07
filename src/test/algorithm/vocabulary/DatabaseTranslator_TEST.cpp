//
// Created by Przemek Piórkowski on 08.04.2016.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE FEITR_DatabaseTranslator_test

#include <iostream>
#include "test_global.h"
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>
#include "src/main/algorithm/vocabulary/kmeans/KMeansVocabularyBuilder.h"
#include "src/main/algorithm/vocabulary/DatabaseTranslator.h"

using namespace feitir;

struct DatabaseTranslatorFixture {
    const DatabaseFactory databaseFactory;
    const std::string resourcesPath;
    const int means;

    DatabaseTranslatorFixture() : resourcesPath{resourcesRootDir() + "database/image/"},
                                  means{5} { }

    ~DatabaseTranslatorFixture() { }
};

BOOST_FIXTURE_TEST_SUITE(DatabaseTranslator_TEST, DatabaseTranslatorFixture)

    BOOST_AUTO_TEST_CASE(TransformDatabaseWithVocabulary)
    {
        auto database = databaseFactory.createDatabase(resourcesPath);

        BOOST_REQUIRE(database != nullptr);
        BOOST_CHECK_EQUAL(database->getImages().size(), 1);
        BOOST_CHECK_EQUAL(database->getCategories().size(), 0);

        auto img = database->getImages()[0];

        BOOST_REQUIRE(img != nullptr);
        BOOST_CHECK_EQUAL(img->getMatches().size(), 0);
        BOOST_CHECK_GT(img->getDescriptors().rows, 0);

        KMeansVocabularyBuilder kMeansVocabularyBuilder;
        DatabaseTranslator databaseTranslator;
        auto vocabulary = kMeansVocabularyBuilder.build(std::make_shared<KMeansParameter>(img->getDescriptors(), means));
        auto transformedDatabase = databaseTranslator.transformDatabase(vocabulary, database);

        BOOST_REQUIRE(transformedDatabase != nullptr);
        BOOST_CHECK_EQUAL(transformedDatabase->getImages().size(), 1);
        BOOST_CHECK_EQUAL(transformedDatabase->getCategories().size(), 0);

        auto transformedImage = transformedDatabase->getImages()[0];

        BOOST_REQUIRE(transformedImage != nullptr);
        BOOST_CHECK_GT(transformedImage->getMatches().size(), 0);
        BOOST_CHECK_EQUAL(transformedImage->getDescriptors().rows, 0);
    }

BOOST_AUTO_TEST_SUITE_END()