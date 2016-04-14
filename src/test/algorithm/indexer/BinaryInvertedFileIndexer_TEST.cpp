//
// Created by Przemek Piórkowski on 14.04.2016.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE FEITR_BinaryInvertedFileIndexer_test

#include <iostream>
#include "test_global.h"
#include <boost/test/unit_test.hpp>
#include "src/main/algorithm/BSIFT/descriptor_median/DescriptorMedianBSIFTExtractor.h"
#include "src/main/database/DatabaseFactory.h"
#include "src/main/algorithm/vocabulary/kmeans/KMeansVocabularyBuilder.h"
#include "src/main/algorithm/indexer/binary_inverted_file/BinaryInvertedFileIndexer.h"

using namespace feitir;

struct BinaryInvertedFileIndexerFixture {
    const std::string resourcePath;
    const std::string thirdRoot;
    const std::string imagePath;
    const int means;
    DescriptorMedianBSIFTExtractor bsiftExtractor;
    DescriptorMedianBSIFTExtractor::DatabaseTranslatorPtr databaseTranslator;
    DatabaseFactory databaseFactory;
    ImageFactory imageFactory;
    KMeansVocabularyBuilder vocabularyBuilder;


    BinaryInvertedFileIndexerFixture() : resourcePath{resourcesRootDir() + "database/"},
                                         thirdRoot{"dir3/"},
                                         imagePath{"image/Lenna.png"},
                                         means{10} {
        databaseTranslator = bsiftExtractor.getDatabaseTranslatorPtr();
    }
};

BOOST_FIXTURE_TEST_SUITE(BinaryInvertedFileIndexer_TEST, BinaryInvertedFileIndexerFixture)

    BOOST_AUTO_TEST_CASE(FirstTestCase)
    {
        auto database = databaseFactory.createDatabase(resourcePath + thirdRoot);
        BOOST_REQUIRE(database != nullptr);

        auto image = bsiftExtractor.extractImageBSIFT(imageFactory.createImage(resourcePath + imagePath));
        BOOST_REQUIRE(image != nullptr);

        auto kMeansParameters = std::make_shared<KMeansParameter>(database, means);
        BOOST_REQUIRE(kMeansParameters != nullptr);

        unsigned sum = 0;
        for (auto& img : database->getImages()) {
            sum += img->getDescriptors().rows;
        }
        for (auto& cat : database->getCategories()) {
            for (auto& img : cat->getImages()) {
                sum += img->getDescriptors().rows;
            }
        }

        BOOST_REQUIRE_EQUAL(kMeansParameters->getData().rows, sum);

        auto vocabulary = vocabularyBuilder.build(kMeansParameters);
        BOOST_REQUIRE(vocabulary != nullptr);

        auto bsiftDatabase = bsiftExtractor.extractDatabaseBSIFT(database);
        BOOST_REQUIRE(bsiftDatabase != nullptr);

        auto transformedDatabase = databaseTranslator->transformDatabase(vocabulary, bsiftDatabase);
        BOOST_REQUIRE(transformedDatabase != nullptr);

        BinaryInvertedFileIndexer<128> binaryInvertedFileIndexer(std::make_shared<BIFParameters>(transformedDatabase, vocabulary, 30));
        auto result = binaryInvertedFileIndexer.query(std::make_shared<BIFQuery<128>>(databaseTranslator->transformImage(vocabulary, image)));

        BOOST_REQUIRE(result != nullptr);
        BOOST_REQUIRE_EQUAL(result->getResultList().size(), 11);
    }

BOOST_AUTO_TEST_SUITE_END()