//
// Created by Przemek Piórkowski on 04.04.2016.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE FEITR_InvertedFileIndexer_test

#include <iostream>
#include <boost/test/unit_test.hpp>
#include <boost/uuid/uuid.hpp>

#include "test_global.h"
#include "src/main/database/DatabaseFactory.h"
#include "src/main/algorithm/indexer/inverted_file/InvertedFileIndexer.h"
#include "src/main/algorithm/vocabulary/kmeans/KMeansVocabularyBuilder.h"
#include "src/main/algorithm/vocabulary/DatabaseTranslator.h"

using namespace feitir;

struct InvertedFileIndexerFixture {
    const std::string resourcePath;
    const std::string thirdRoot;
    const std::string imagePath;
    const int means;
    DatabaseFactory databaseFactory;
    ImageFactory imageFactory;
    KMeansVocabularyBuilder vocabularyBuilder;
    DatabaseTranslator databaseTranslator;


    InvertedFileIndexerFixture() : resourcePath{resourcesRootDir() + "database/"},
                                   thirdRoot{"dir3/"},
                                   imagePath{"image/Lenna.png"},
                                   means{10} {

    }
};

BOOST_FIXTURE_TEST_SUITE(InvertedFileIndexer_TEST, InvertedFileIndexerFixture)

    BOOST_AUTO_TEST_CASE(FirstTestCase)
    {
        auto database = databaseFactory.createDatabase(resourcePath + thirdRoot);
        auto image = imageFactory.createImage(resourcePath + imagePath);
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
        BOOST_REQUIRE(image != nullptr);
        auto vocabulary = vocabularyBuilder.build(std::make_shared<KMeansParameter>(database, means));
        auto transformedDatabase = databaseTranslator.transformDatabase(vocabulary, database);

        InvertedFileIndexer indexer(std::make_shared<IFParameters>(transformedDatabase));
        auto result = indexer.query(std::make_shared<IFQuery>(databaseTranslator.transformImage(vocabulary, image)));
        BOOST_REQUIRE(result != nullptr);
        BOOST_REQUIRE_EQUAL(result->getResultList().size(), 11);
    }

BOOST_AUTO_TEST_SUITE_END()