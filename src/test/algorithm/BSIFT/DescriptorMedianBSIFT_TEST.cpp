//
// Created by Przemek Piórkowski on 20.03.2016.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE FEITR_DescriptorMedianBSIFTExtractor_test

#include <iostream>
#include "test_global.h"
#include <boost/test/unit_test.hpp>
#include "src/main/algorithm/BSIFT/DescriptorMedianBSIFTExtractor.h"
#include "src/main/database/image/ImageFactory.h"

using namespace feitir;

struct DescriptorMedianBSIFTExtractorFixture {
    const std::string resourcePath;
    const std::string imagePath;
    const std::string lennaImage;
    const std::string firstDirPath;
    const std::string secondDirPath;
    const std::string thirdDirPath;
    ImageFactory imageFactory;
    DescriptorMedianBSIFTExtractor descriptorMedianBSIFT;

    DescriptorMedianBSIFTExtractorFixture() : resourcePath{resourcesRootDir() + "database/"},
                                              imagePath{"image/"},
                                              lennaImage{"Lenna.png"},
                                              firstDirPath{"dir1/"},
                                              secondDirPath{"dir2/"},
                                              thirdDirPath{"dir3/"} {

    }

    float dummyMedianFind(const std::vector<float>& val) {
        std::vector<float> localCopy(val);
        std::sort(localCopy.begin(), localCopy.end());

        if (localCopy.size() & 0x1) {
            return localCopy[(localCopy.size()-1)/2];
        } else {
            return (localCopy[localCopy.size()/2] + localCopy[(localCopy.size()/2)-1])/2;
        }
    }

    std::vector<bool> medianBinaryDescriptor(cv::Mat row) {
        std::vector<float> vec(row.cols);
        for (int i = 0; i < row.cols; ++i) {
            vec[i] = row.at<float>(0, i);
        }

        float median = dummyMedianFind(vec);
        std::vector<bool> binaryDescriptor(row.cols);

        for (int i = 0; i < row.cols; ++i) {
            binaryDescriptor[i] = vec[i] > median;
        }

        return binaryDescriptor;
    }
};

BOOST_FIXTURE_TEST_SUITE(DescriptorMedianBSIFTExtractor_TEST, DescriptorMedianBSIFTExtractorFixture)

    BOOST_AUTO_TEST_CASE(FirstTestCase)
    {
        auto img = imageFactory.createImage(resourcePath + imagePath + lennaImage);
        BOOST_REQUIRE(img != nullptr);
        auto bsiftImg = descriptorMedianBSIFT.extractImageBSIFT(img);
        BOOST_REQUIRE(bsiftImg != nullptr);

        for (int i = 0; i < bsiftImg->getDescriptors().rows; ++i) {
            std::vector<bool> bdescriptor = medianBinaryDescriptor(bsiftImg->getDescriptors().row(i));
            BOOST_REQUIRE_EQUAL_COLLECTIONS(bsiftImg->getBsift()[i].begin(), bsiftImg->getBsift()[i].end(),
                                            bdescriptor.begin(), bdescriptor.end());
        }
    }

    BOOST_AUTO_TEST_CASE(DummyMedianTest)
    {
        BOOST_REQUIRE_CLOSE_FRACTION(dummyMedianFind({1, 2, 3}), 2, 0.1);
        BOOST_REQUIRE_CLOSE_FRACTION(dummyMedianFind({1, 2, 3, 4}), 2.5, 0.1);
    }

BOOST_AUTO_TEST_SUITE_END()