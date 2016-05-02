//
// Created by Przemek Piórkowski on 29.04.2016.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE FEITR_ComparasionArrayBSIFTExtractor_test

#include <iostream>
#include "test_global.h"
#include <boost/test/unit_test.hpp>
#include "src/main/algorithm/BSIFT/comparasion_array/ComparasionArrayBSIFTExtractor.h"
#include "src/main/database/DatabaseFactory.h"
#include "src/main/database/image/ImageFactory.h"

using namespace feitir;

struct ComparasionArrayBSIFTExtractorFixture {
    const std::string resourcePath;
    const std::string imagePath;
    const std::string lennaImage;
    static constexpr unsigned L = 64;
    const unsigned T = 20;
    ImageFactory imageFactory;
    DatabaseFactory databaseFactory;

    ComparasionArrayBSIFTExtractorFixture() : resourcePath{resourcesRootDir() + "database/"},
                                              imagePath{"image/"},
                                              lennaImage{"Lenna.png"} { }

};

BOOST_FIXTURE_TEST_SUITE(ComparasionArrayBSIFTExtractor_TEST, ComparasionArrayBSIFTExtractorFixture)

    BOOST_AUTO_TEST_CASE(FirstTestCase)
    {
        auto img = imageFactory.createImage(resourcePath + imagePath + lennaImage);
        BOOST_REQUIRE(img != nullptr);
        ComparasionArrayBSIFTExtractor<L> extractor(L, T);
        auto bsiftImg = extractor.extractImageBSIFT(img);
        BOOST_REQUIRE(bsiftImg != nullptr);
        BOOST_REQUIRE(bsiftImg->getBsift()[0].size() == L);
    }

    BOOST_AUTO_TEST_CASE(SecondTestCase)
    {
        auto img = imageFactory.createImage(resourcePath + imagePath + lennaImage);
        BOOST_REQUIRE(img != nullptr);
        auto fakeImg = imageFactory.createImage(img, cv::Mat::zeros(10, 256, CV_32F));
        ComparasionArrayBSIFTExtractor<L> extractor(L, T);
        auto fakeBsiftImg = extractor.extractImageBSIFT(fakeImg);
        BOOST_REQUIRE(fakeBsiftImg != nullptr);
        for (auto bsift : fakeBsiftImg->getBsift()) {
            BOOST_REQUIRE(bsift.size() == L);
            BOOST_REQUIRE(bsift.count() == 0);
        }
    }

    BOOST_AUTO_TEST_CASE(ThirdTestCase)
    {
        auto img = imageFactory.createImage(resourcePath + imagePath + lennaImage);
        BOOST_REQUIRE(img != nullptr);
        std::vector<float> singleDescValue;
        float currVal = 0;
        for (int i = 0; i < 256; ++i) {
            currVal += (T + 1);
            singleDescValue.push_back(currVal);
        }
        BOOST_REQUIRE(singleDescValue.size() == 256);

        cv::Mat fakeDescriptors(20, 256, CV_32F);
        for (int i = 0; i < 20; ++i) {
            for (int j = 0; j < singleDescValue.size(); ++j) {
                fakeDescriptors.at<float>(i, j) = singleDescValue[j];
            }
        }
        BOOST_REQUIRE(fakeDescriptors.rows == 20);
        BOOST_REQUIRE(fakeDescriptors.cols == 256);

        auto fakeImg = imageFactory.createImage(img, fakeDescriptors);
        ComparasionArrayBSIFTExtractor<L> extractor(L, T);
        auto fakeBsiftImg = extractor.extractImageBSIFT(fakeImg);
        BOOST_REQUIRE(fakeBsiftImg != nullptr);

        for (auto bsift : fakeBsiftImg->getBsift()) {
            BOOST_REQUIRE(bsift.size() == L);
            BOOST_REQUIRE(bsift.count() == L);
        }
    }

BOOST_AUTO_TEST_SUITE_END()