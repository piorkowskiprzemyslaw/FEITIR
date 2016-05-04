//
// Created by Przemek Piórkowski on 03.05.2016.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE FEITR_LocalitySensitiveHashingBSIFTExtractor_test

#include <iostream>
#include "test_global.h"
#include <boost/test/unit_test.hpp>
#include "src/main/algorithm/BSIFT/locality_sensitive_hashing/LocalitySensitiveHashingBSIFTExtractor.h"
#include "src/main/database/DatabaseFactory.h"
#include "src/main/database/image/ImageFactory.h"

using namespace feitir;

struct LocalitySensitiveHashingBSIFTExtractorFixture {
    const std::string resourcePath;
    const std::string imagePath;
    const std::string lennaImage;
    const std::string databaseDir;
    static constexpr unsigned N = 128;
    ImageFactory imageFactory;
    DatabaseFactory databaseFactory;

    LocalitySensitiveHashingBSIFTExtractorFixture() : resourcePath{resourcesRootDir() + "database/"},
                                                      imagePath{"image/"},
                                                      lennaImage{"Lenna.png"},
                                                      databaseDir{"dir3"} { }

};

BOOST_FIXTURE_TEST_SUITE(LocalitySensitiveHashingBSIFTExtractor_TEST, LocalitySensitiveHashingBSIFTExtractorFixture)

    BOOST_AUTO_TEST_CASE(Database)
    {
        auto hashFunctions = LocalitySensitiveHashingBSIFTExtractor<N>::generateRandomHashFunctions();
        LocalitySensitiveHashingBSIFTExtractor<N> extractor(hashFunctions);

        auto database = databaseFactory.createDatabase(resourcePath + imagePath);
        BOOST_REQUIRE(database != nullptr);
        auto transformedDatabase = extractor.extractDatabaseBSIFT(database);
    }

    BOOST_AUTO_TEST_CASE(SingleImage)
    {
        auto hashFunctions = LocalitySensitiveHashingBSIFTExtractor<N>::generateRandomHashFunctions();
        LocalitySensitiveHashingBSIFTExtractor<N> extractor(hashFunctions);

        auto img = imageFactory.createImage(resourcePath + imagePath + lennaImage);
        BOOST_REQUIRE(img != nullptr);
        auto bsiftImg = extractor.extractImageBSIFT(img);
        BOOST_REQUIRE(bsiftImg != nullptr);
        for (auto bsift : bsiftImg->getBsift()) {
            BOOST_REQUIRE(bsift.size() == N);
            BOOST_REQUIRE(bsift.count() > 0);
            BOOST_REQUIRE(bsift.count() < N);
        }
    }

BOOST_AUTO_TEST_SUITE_END()