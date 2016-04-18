//
// Created by Przemek Piórkowski on 15.04.2016.
//


#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE FEITR_SupportingWordsInvertedFileIndexer_test

#include <iostream>
#include "test_global.h"
#include <boost/test/unit_test.hpp>
#include "src/main/database/image/ImageFactory.h"
#include "src/main/database/DatabaseFactory.h"
#include "src/main/algorithm/BSIFT/descriptor_median/DescriptorMedianBSIFTExtractor.h"
#include "src/main/algorithm/vocabulary/DatabaseTranslator.h"
#include "src/main/algorithm/indexer/supporting_words_inverted_file/SupportingWordsInvertedFileIndexer.h"
#include "src/main/algorithm/vocabulary/kmeans/KMeansVocabularyBuilder.h"

using namespace feitir;

struct SupportingWordsInvertedFileIndexerFixture {
    const std::string resourcePath;
    const std::string thirdRoot;
    const std::string imagePath;
    const int means;
    ImageFactory imageFactory;
    DatabaseFactory databaseFactory;
    DescriptorMedianBSIFTExtractor bsiftExtractor;
    DescriptorMedianBSIFTExtractor::DatabaseTranslatorPtr databaseTranslator;
    KMeansVocabularyBuilder vocabularyBuilder;


    SupportingWordsInvertedFileIndexerFixture() : resourcePath{resourcesRootDir() + "database/"},
                                                  thirdRoot{"dir3/"},
                                                  imagePath{"image/Lenna.png"},
                                                  means{10} {
        databaseTranslator = bsiftExtractor.getDatabaseTranslatorPtr();
    }
};

BOOST_FIXTURE_TEST_SUITE(SupportingWordsInvertedFileIndexer_TEST, SupportingWordsInvertedFileIndexerFixture)

    BOOST_AUTO_TEST_CASE(FirstTestCase)
    {
        auto database = databaseFactory.createDatabase(resourcePath + thirdRoot);
        BOOST_REQUIRE(database != nullptr);

        auto originalImage = imageFactory.createImage(resourcePath + imagePath);
        BOOST_REQUIRE(originalImage != nullptr);

        auto image = bsiftExtractor.extractImageBSIFT(originalImage);
        BOOST_REQUIRE(image != nullptr);

        auto vocabulary = vocabularyBuilder.build(std::make_shared<KMeansParameter>(database, means));
        BOOST_REQUIRE(vocabulary != nullptr);

        auto transformedDatabase = databaseTranslator->transformDatabase(vocabulary,
                                                                         bsiftExtractor.extractDatabaseBSIFT(database));
        BOOST_REQUIRE(transformedDatabase != nullptr);

        SupportingWordsInvertedFileIndexer<128> indexer(
                std::make_shared<SWIFParameters>(3, 30, 2, transformedDatabase, vocabulary));

        auto result = indexer.query(
                std::make_shared<SWIFQuery<128>>(image,
                                                 std::dynamic_pointer_cast<ImageBSIFT<128>>(databaseTranslator->transformImage(vocabulary, image))));

        BOOST_REQUIRE(result != nullptr);
        BOOST_REQUIRE_EQUAL(result->getResultList().size(), 11);
    }

BOOST_AUTO_TEST_SUITE_END()