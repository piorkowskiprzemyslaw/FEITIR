//
// Created by Przemek Piórkowski on 08.07.2016.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE FEITR_CrossIndexer_test

#include <iostream>
#include <boost/test/unit_test.hpp>
#include <boost/uuid/uuid.hpp>
#include <src/main/algorithm/BSIFT/descriptor_median/DescriptorMedianBSIFTExtractor.h>
#include "src/main/algorithm/vocabulary/kmeans/KMeansVocabularyBuilder.h"
#include "src/main/algorithm/indexer/cross_indexer/CrossIndexer.h"

#include "test_global.h"

using namespace feitir;

struct CrossIndexerFixture {
    const std::string resourcePath;
    const std::string thirdRoot;
    const std::string imagePath;
    ImageFactory imageFactory;
    DescriptorMedianBSIFTExtractor extractor;
    DatabaseFactory databaseFactory;
    KMeansVocabularyBuilder vocabularyBuilder;
    BSIFTExtractor::DatabaseTranslatorPtr databaseTranslator;

    CrossIndexerFixture() : resourcePath{resourcesRootDir() + "database/"},
                            imagePath{"image/Lenna.png"},
                            thirdRoot{"dir3/"} {
        databaseTranslator = extractor.getDatabaseTranslatorPtr();
    }
};

BOOST_FIXTURE_TEST_SUITE(CrossIndexer_TEST, CrossIndexerFixture)

    BOOST_AUTO_TEST_CASE(BasicTestCase)
    {
        auto database = databaseFactory.createDatabase(resourcePath + thirdRoot);
        BOOST_REQUIRE(database != nullptr);

        auto vocabulary = vocabularyBuilder.build(std::make_shared<KMeansParameter>(database, 10));
        BOOST_REQUIRE(vocabulary != nullptr);

        auto transformedDb = databaseTranslator->transformDatabase(vocabulary,
                                                                   extractor.extractDatabaseBSIFT(database));
        BOOST_REQUIRE(transformedDb != nullptr);

        auto matchingFunction = [] (int vwIdx, const boost::uuids::uuid& imUUID) {
            return 1;
        };

        CrossIndexer indexer(transformedDb, vocabulary, matchingFunction, 5, 30);

        auto queryImage = extractor.extractImageBSIFT(imageFactory.createImage(resourcePath + imagePath));
        BOOST_REQUIRE(queryImage != nullptr);

        auto result = indexer.query(std::make_shared<CrossQuery>(std::dynamic_pointer_cast<ImageBSIFT>(
                databaseTranslator->transformImage(vocabulary, queryImage))));


        BOOST_REQUIRE(result != nullptr);
    }

    BOOST_AUTO_TEST_CASE(expandCodeWordTest)
    {
        auto database = databaseFactory.createDatabase(resourcePath + thirdRoot);
        BOOST_REQUIRE(database != nullptr);

        auto vocabulary = vocabularyBuilder.build(std::make_shared<KMeansParameter>(database, 10));
        BOOST_REQUIRE(vocabulary != nullptr);

        auto transformedDb = databaseTranslator->transformDatabase(vocabulary,
                                                                   extractor.extractDatabaseBSIFT(database));
        BOOST_REQUIRE(transformedDb != nullptr);

        CrossIndexer indexer(transformedDb, vocabulary,
                             [] (int vwIdx, const boost::uuids::uuid& imUUID) { return 1; }, 0,0, 2, 4);

        std::vector<std::string> codeWordStrings = { "1010", "0010", "1110", "1000", "1011", "0110",
                                                     "0000", "0011", "1100", "1111", "1001"};
        const ImageBSIFT::BSIFT codeWord(codeWordStrings[0], 0, codeWordStrings[0].size());
        auto expandedCodeWords = indexer.expandCodeWord(codeWord, 2);

        BOOST_REQUIRE_EQUAL(expandedCodeWords.size(), codeWordStrings.size());
        for (const auto & codeWordString : codeWordStrings) {
            BOOST_REQUIRE(std::find(expandedCodeWords.begin(), expandedCodeWords.end(),
                                    ImageBSIFT::BSIFT(codeWordString, 0, codeWordString.size()))
                          != expandedCodeWords.end());
        }
    }

    BOOST_AUTO_TEST_CASE(generateCodeWordTest)
    {
        auto database = databaseFactory.createDatabase(resourcePath + thirdRoot);
        BOOST_REQUIRE(database != nullptr);

        auto vocabulary = vocabularyBuilder.build(std::make_shared<KMeansParameter>(database, 10));
        BOOST_REQUIRE(vocabulary != nullptr);

        auto transformedDb = databaseTranslator->transformDatabase(vocabulary,
                                                                   extractor.extractDatabaseBSIFT(database));
        BOOST_REQUIRE(transformedDb != nullptr);

        CrossIndexer indexer(transformedDb, vocabulary,
                             [] (int vwIdx, const boost::uuids::uuid& imUUID) { return 1; }, 0,0, 2, 6);

        std::vector<std::string> codeWordStrings = { "111111000000",
                                                     "000000111111",
                                                     "101010101010",
                                                     "010101010101"};

        for (const auto & codeWordString : codeWordStrings) {
            BOOST_REQUIRE_EQUAL(ImageBSIFT::BSIFT(codeWordString, 0, 6),
                                indexer.generateCodeWord(ImageBSIFT::BSIFT(codeWordString, 0, codeWordString.size())));
        }
    }

BOOST_AUTO_TEST_SUITE_END()