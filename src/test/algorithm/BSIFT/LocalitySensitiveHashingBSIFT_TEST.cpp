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
    static constexpr unsigned N = 256;
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
        BOOST_REQUIRE(true);
        auto hashFunctions = LocalitySensitiveHashingBSIFTExtractor::generateRandomHashFunctions(N);
        BOOST_REQUIRE(true);
        LocalitySensitiveHashingBSIFTExtractor extractor(N, hashFunctions);
        BOOST_REQUIRE(true);
        auto database = databaseFactory.createDatabase(resourcePath + imagePath);
        BOOST_REQUIRE(database != nullptr);
        auto transformedDatabase = extractor.extractDatabaseBSIFT(database);
    }


BOOST_AUTO_TEST_SUITE_END()