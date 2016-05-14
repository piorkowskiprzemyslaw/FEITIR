//
// Created by Przemek Piórkowski on 02.05.2016.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE FEITR_DescriptorPositionMedianBSIFTExtractor_test

#include <iostream>
#include "test_global.h"
#include <boost/test/unit_test.hpp>
#include "src/main/algorithm/BSIFT/descriptor_position_median/DescriptorPositionMedianBSIFTExtractor.h"
#include "src/main/database/DatabaseFactory.h"
#include "src/main/database/image/ImageFactory.h"

using namespace feitir;

struct DescriptorPositionMedianBSIFTExtractorFixture {
    const std::string resourcePath;
    const std::string imagePath;
    const std::string lennaImage;
    const std::string databaseDir;
    ImageFactory imageFactory;
    DatabaseFactory databaseFactory;

    DescriptorPositionMedianBSIFTExtractorFixture() : resourcePath{resourcesRootDir() + "database/"},
                                                      imagePath{"image/"},
                                                      lennaImage{"Lenna.png"},
                                                      databaseDir{"dir3"} { }

};

BOOST_FIXTURE_TEST_SUITE(DescriptorPositionMedianBSIFTExtractor_TEST, DescriptorPositionMedianBSIFTExtractorFixture)

    BOOST_AUTO_TEST_CASE(FirstTestCase)
    {
        DescriptorPositionMedianBSIFTExtractor extractor;

        auto img = imageFactory.createImage(resourcePath + imagePath + lennaImage);
        BOOST_REQUIRE(img != nullptr);
        BOOST_CHECK_THROW(extractor.extractImageBSIFT(img), std::logic_error);
    }

    BOOST_AUTO_TEST_CASE(SecondTestCase)
    {
        DescriptorPositionMedianBSIFTExtractor extractor;

        auto database = databaseFactory.createDatabase(resourcePath + imagePath);
        BOOST_REQUIRE(database != nullptr);
        BOOST_CHECK_NO_THROW(extractor.extractDatabaseBSIFT(database));
    }

    BOOST_AUTO_TEST_CASE(ThirdTestCase)
    {
        DescriptorPositionMedianBSIFTExtractor extractor;

        auto database = databaseFactory.createDatabase(resourcePath + databaseDir);
        BOOST_REQUIRE(database != nullptr);
        std::vector<ImagePtr> fakeImages;
        int counter = 1;
        for (auto img : *database) {
            cv::Mat fakeDescriptor = cv::Mat::ones(1, img->getDescriptors().cols, CV_32F);
            fakeDescriptor *= (counter ++);
            fakeImages.push_back(imageFactory.createImage(img, fakeDescriptor));
        }

        auto fakeDatabase = databaseFactory.createDatabase(database, std::vector<CategoryPtr>(), fakeImages);
        auto transformedDatabase = extractor.extractDatabaseBSIFT(fakeDatabase);

        BOOST_REQUIRE(transformedDatabase != nullptr);
        BOOST_REQUIRE_EQUAL(transformedDatabase->getImages().size(), fakeImages.size());

        for (unsigned i = 0; i < transformedDatabase->getImages().size(); ++i) {
            DescriptorPositionMedianBSIFTExtractor::ImageBSIFTPtr bsiftImg
                    = std::dynamic_pointer_cast<DescriptorPositionMedianBSIFTExtractor::ImageBSIFT>(
                            transformedDatabase->getImages()[i]);

            BOOST_REQUIRE(bsiftImg != nullptr);
            BOOST_REQUIRE_EQUAL(bsiftImg->getBsift().size(), 1);

            if (i <= transformedDatabase->getImages().size() / 2) {
                BOOST_REQUIRE_EQUAL(bsiftImg->getBsift()[0].count(), 0);
            } else {
                BOOST_REQUIRE_EQUAL(bsiftImg->getBsift()[0].count(), bsiftImg->getBsift()[0].size());
            }
        }
    }

BOOST_AUTO_TEST_SUITE_END()