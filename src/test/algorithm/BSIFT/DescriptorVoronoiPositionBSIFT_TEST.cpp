//
// Created by Przemek Piórkowski on 16.05.2016.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE FEITR_DescriptorVoronoiPositionBSIFTExtractor_test

#include <iostream>
#include "test_global.h"
#include <boost/test/unit_test.hpp>
#include <src/main/algorithm/vocabulary/kmeans/KMeansVocabularyBuilder.h>
#include "src/main/algorithm/BSIFT/descriptor_voronoi_position/DescriptorVoronoiPositionBSIFTExtractor.h"

using namespace feitir;

struct DescriptorVoronoiPositionBSIFTExtractorFixture {
    const std::string resourcePath;
    const std::string imagePath;
    const std::string lennaImage;
    const std::string databaseDir;
    ImageFactory imageFactory;
    DatabaseFactory databaseFactory;

    DescriptorVoronoiPositionBSIFTExtractorFixture() : resourcePath{resourcesRootDir() + "database/"},
                                                       imagePath{"image/"},
                                                       lennaImage{"Lenna.png"},
                                                       databaseDir{"dir3"} { }

};

BOOST_FIXTURE_TEST_SUITE(DescriptorVoronoiPositionBSIFTExtractor_TEST, DescriptorVoronoiPositionBSIFTExtractorFixture)

    BOOST_AUTO_TEST_CASE(FirstTestCase)
    {
        auto database = databaseFactory.createDatabase(resourcePath + imagePath);
        auto image = imageFactory.createImage(resourcePath + imagePath + lennaImage);
        KMeansVocabularyBuilder kMeansVocabularyBuilder;
        KMeansParameterPtr param = std::make_shared<KMeansParameter>(database, 5);
        auto vocabulary = kMeansVocabularyBuilder.build(param);
        DescriptorVoronoiPositionBSIFTExtractor extractor(64, vocabulary, database);
        auto bsiftImg = extractor.extractImageBSIFT(image);
        BOOST_REQUIRE(bsiftImg != nullptr);
        for (auto bsift : bsiftImg->getBsift()) {
            BOOST_REQUIRE_GT(bsift.count(), 0);
        }
    }

BOOST_AUTO_TEST_SUITE_END()
