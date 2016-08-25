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
#include "src/main/algorithm/vocabulary/hierarchical_kmeans/HKMeansVocabularyBuilder.h"
#include "src/main/algorithm/vocabulary/DatabaseTranslator.h"

using namespace feitir;

struct DatabaseTranslatorFixture {
    const DatabaseFactory databaseFactory;
    const std::string resourcesPath;
    const std::string vocabularyFile;
    const int means;
    const int K;
    const int L;

    DatabaseTranslatorFixture() : resourcesPath{resourcesRootDir() + "database/image/"},
                                  vocabularyFile{"vocabulary.yml"},
                                  means{5}, K{3}, L{2} { }

    ~DatabaseTranslatorFixture() {
        boost::filesystem::remove(resourcesPath + vocabularyFile);
    }
};

BOOST_FIXTURE_TEST_SUITE(DatabaseTranslator_TEST, DatabaseTranslatorFixture)

    BOOST_AUTO_TEST_CASE(TransformDatabaseWithKMeansVocabulary)
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

    BOOST_AUTO_TEST_CASE(TransformDatabaseWithHKMeansVocabulary)
    {
        auto database = databaseFactory.createDatabase(resourcesPath);

        BOOST_REQUIRE(database != nullptr);
        BOOST_CHECK_EQUAL(database->getImages().size(), 1);
        BOOST_CHECK_EQUAL(database->getCategories().size(), 0);

        auto img = database->getImages()[0];

        BOOST_REQUIRE(img != nullptr);
        BOOST_CHECK_EQUAL(img->getMatches().size(), 0);
        BOOST_CHECK_GT(img->getDescriptors().rows, 0);

        HKMeansVocabularyBuilder hkMeansVocabularyBuilder;
        DatabaseTranslator databaseTranslator;
        auto vocabulary = hkMeansVocabularyBuilder.build(std::make_shared<HKMeansParameter>(img->getDescriptors(), K, L));
        auto transformedDatabase = databaseTranslator.transformDatabase(vocabulary, database);

        BOOST_REQUIRE(transformedDatabase != nullptr);
        BOOST_CHECK_EQUAL(transformedDatabase->getImages().size(), 1);
        BOOST_CHECK_EQUAL(transformedDatabase->getCategories().size(), 0);

        auto transformedImage = transformedDatabase->getImages()[0];

        BOOST_REQUIRE(transformedImage != nullptr);
        BOOST_CHECK_GT(transformedImage->getMatches().size(), 0);
        BOOST_CHECK_EQUAL(transformedImage->getDescriptors().rows, 0);

        hkMeansVocabularyBuilder.saveToFile(vocabulary, resourcesPath + vocabularyFile);
        auto vocabularyFromFile = hkMeansVocabularyBuilder.readFromFile(resourcesPath + vocabularyFile);
        auto transformedImage1 = databaseTranslator.transformImage(vocabularyFromFile, img);

        BOOST_REQUIRE(transformedImage1 != nullptr);
        BOOST_CHECK_GT(transformedImage1->getMatches().size(), 0);
        BOOST_CHECK_EQUAL(transformedImage1->getMatches().size(), transformedImage->getMatches().size());
        BOOST_CHECK_EQUAL(transformedImage1->getDescriptors().rows, 0);

        for (int i = 0; i < transformedImage1->getMatches().size(); ++i) {
            BOOST_REQUIRE_EQUAL(transformedImage->getMatches()[i].queryIdx,
                                transformedImage1->getMatches()[i].queryIdx);
            BOOST_REQUIRE_EQUAL(transformedImage->getMatches()[i].trainIdx,
                                transformedImage1->getMatches()[i].trainIdx);
        }
    }

BOOST_AUTO_TEST_SUITE_END()