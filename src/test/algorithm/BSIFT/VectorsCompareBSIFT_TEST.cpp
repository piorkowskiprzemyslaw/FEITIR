//
// Created by Przemek Piórkowski on 12.05.2016.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE FEITR_VectorsCompareBSIFTExtractor_test

#include <iostream>
#include "test_global.h"
#include <boost/test/unit_test.hpp>
#include "src/main/algorithm/BSIFT/vectors_compare/VectorsCompareBSIFTExtractor.h"

using namespace feitir;

struct VectorsCompareBSIFTExtractorFixture {
    const std::string resourcePath;
    const std::string imagePath;
    const std::string lennaImage;
    const std::string databaseDir;
    ImageFactory imageFactory;
    DatabaseFactory databaseFactory;

    VectorsCompareBSIFTExtractorFixture() : resourcePath{resourcesRootDir() + "database/"},
                                            imagePath{"image/"},
                                            lennaImage{"Lenna.png"},
                                            databaseDir{"dir3"} { }

};

BOOST_FIXTURE_TEST_SUITE(VectorsCompareBSIFTExtractor_TEST, VectorsCompareBSIFTExtractorFixture)

    BOOST_AUTO_TEST_CASE(DeepTestCase)
    {
        VectorsCompareBSIFTExtractor extractor;
        auto img = imageFactory.createImage(resourcePath + imagePath + lennaImage);
        float fakeDescriptorData[128] = {1, 2, 3, 4, 5, 6, 7, 8,
                                         8, 7, 6, 5, 4, 3, 2, 1,
                                         9, 6, 7, 4, 5, 2, 3, 0,
                                         10, 7, 8, 5, 6, 3, 4, 1,
                                         10, 7, 8, 5, 6, 7, 8, 9,
                                         7, 6, 5, 4, 3, 2, 1, 0,
                                         8, 7, 6, 5, 4, 3, 2, 1,
                                         11, 6, 9, 4, 7, 2, 5, 0,
                                         1, 2, 3, 4, 5, 6, 7, 8,
                                         8, 7, 6, 5, 4, 3, 2, 1,
                                         9, 6, 7, 4, 5, 2, 3, 0,
                                         10, 7, 8, 5, 6, 3, 4, 1,
                                         10, 7, 8, 5, 6, 7, 8, 9,
                                         7, 6, 5, 4, 3, 2, 1, 0,
                                         8, 7, 6, 5, 4, 3, 2, 1,
                                         11, 6, 9, 4, 7, 2, 5, 0};
        cv::Mat fakeDescriptor = cv::Mat(1, img->getDescriptors().cols, CV_32F, fakeDescriptorData);
        std::string expectedResultString =  "00000001" "00001111" "00000000"
                                            "11111110" "01010101" "11111111"
                                            "10101010" "00000000" "10101010"
                                            "10101010" "11111000" "01010101"
                                            "10100000" "11111111" "11111111"
                                            "11111110" "00000000" "00000000"
                                            "11111110" "01010101" "01010101"
                                            "10101010" "10101000" "10101010"
                                            "00000001" "00001111" "00000000"
                                            "11111110" "01010101" "11111111"
                                            "10101010" "00000000" "10101010"
                                            "10101010" "11111000" "01010101"
                                            "10100000" "11111111" "11111111"
                                            "11111110" "00000000" "00000000"
                                            "11111110" "01010101" "01010101"
                                            "10101010" "10101000" "10101010";
        std::reverse(expectedResultString.begin(), expectedResultString.end());
        VectorsCompareBSIFTExtractor::BSIFT expectedResult(expectedResultString, 0,
                                                           expectedResultString.size());

        auto fakeImg = imageFactory.createImage(img, fakeDescriptor);
        auto fakeBSIFTImg = extractor.extractImageBSIFT(fakeImg);
        BOOST_REQUIRE(fakeBSIFTImg != nullptr);
        BOOST_REQUIRE_EQUAL(fakeBSIFTImg->getBsift().size(), 1);
        BOOST_REQUIRE_EQUAL((fakeBSIFTImg->getBsift()[0]^expectedResult).count(), 0);
    }

BOOST_AUTO_TEST_SUITE_END()