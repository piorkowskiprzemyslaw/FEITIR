//
// Created by Przemek Piórkowski on 20.03.2016.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE FEITR_DescriptorMedianBSIFTExtractor_test

#include <iostream>
#include "test_global.h"
#include <boost/test/unit_test.hpp>
#include "src/main/algorithm/BSIFT/descriptor_median/DescriptorMedianBSIFTExtractor.h"
#include "src/main/algorithm/vocabulary/kmeans/KMeansVocabularyBuilder.h"
#include "src/main/database/DatabaseFactory.h"
#include "src/main/database/image/ImageFactory.h"

using namespace feitir;

struct DescriptorMedianBSIFTExtractorFixture {
    const std::string resourcePath;
    const std::string imagePath;
    const std::string lennaImage;
    ImageFactory imageFactory;
    DatabaseFactory databaseFactory;
    int means;
    DescriptorMedianBSIFTExtractor descriptorMedianBSIFT;

    DescriptorMedianBSIFTExtractorFixture() : resourcePath{resourcesRootDir() + "database/"},
                                              imagePath{"image/"},
                                              lennaImage{"Lenna.png"},
                                              means{5} { }

    float dummyMedianFind(const std::vector<float>& val) {
        std::vector<float> localCopy(val);
        std::sort(localCopy.begin(), localCopy.end());

        if (localCopy.size() & 0x1) {
            return localCopy[(localCopy.size()-1)/2];
        } else {
            return (localCopy[localCopy.size()/2] + localCopy[(localCopy.size()/2)-1])/2;
        }
    }

    std::bitset<128> medianBinaryDescriptor(cv::Mat row) {
        std::vector<float> vec(row.cols);
        for (int i = 0; i < row.cols; ++i) {
            vec[i] = row.at<float>(0, i);
        }

        float median = dummyMedianFind(vec);
        std::bitset<128> binaryDescriptor;

        for (int i = 0; i < row.cols; ++i) {
            binaryDescriptor[i] = vec[i] > median;
        }

        return binaryDescriptor;
    }
};

BOOST_FIXTURE_TEST_SUITE(DescriptorMedianBSIFTExtractor_TEST, DescriptorMedianBSIFTExtractorFixture)

    BOOST_AUTO_TEST_CASE(BasicTestCase)
    {
        auto img = imageFactory.createImage(resourcePath + imagePath + lennaImage);
        BOOST_REQUIRE(img != nullptr);
        auto bsiftImg = descriptorMedianBSIFT.extractImageBSIFT(img);
        BOOST_REQUIRE(bsiftImg != nullptr);

        for (int i = 0; i < bsiftImg->getDescriptors().rows; ++i) {
            std::bitset<128> bdescriptor = medianBinaryDescriptor(bsiftImg->getDescriptors().row(i));
            BOOST_REQUIRE(bsiftImg->getBsift()[i] == bdescriptor);
        }
    }

    BOOST_AUTO_TEST_CASE(DummyMedianTest)
    {
        BOOST_REQUIRE_CLOSE_FRACTION(dummyMedianFind({1, 2, 3}), 2, 0.1);
        BOOST_REQUIRE_CLOSE_FRACTION(dummyMedianFind({1, 2, 3, 4}), 2.5, 0.1);
    }

    BOOST_AUTO_TEST_CASE(BSIFTDatabaseTranslator)
    {
        const DatabasePtr database = databaseFactory.createDatabase(resourcePath + imagePath);

        BOOST_REQUIRE(database != nullptr);
        BOOST_CHECK_EQUAL(database->getImages().size(), 1);
        BOOST_CHECK_EQUAL(database->getCategories().size(), 0);

        auto img = database->getImages()[0];

        BOOST_REQUIRE(img != nullptr);
        BOOST_CHECK_EQUAL(img->getMatches().size(), 0);
        BOOST_CHECK_GT(img->getDescriptors().rows, 0);

        KMeansVocabularyBuilder kMeansVocabularyBuilder;
        auto vocabulary = kMeansVocabularyBuilder.build(std::make_shared<KMeansParameter>(img->getDescriptors(), means));

        DescriptorMedianBSIFTExtractor descriptorMedianBSIFTExtractor;
        auto bsiftDatabase = descriptorMedianBSIFTExtractor.extractDatabaseBSIFT(database);

        BOOST_REQUIRE(bsiftDatabase != nullptr);
        BOOST_CHECK_EQUAL(bsiftDatabase->getImages().size(), 1);
        BOOST_CHECK_EQUAL(bsiftDatabase->getCategories().size(), 0);

        auto bsiftPtr = std::dynamic_pointer_cast<DescriptorMedianBSIFTExtractor::ImageBSIFT>(
                bsiftDatabase->getImages()[0]);

        BOOST_REQUIRE(bsiftPtr != nullptr);
        BOOST_CHECK_EQUAL(bsiftPtr->getMatches().size(), 0);
        BOOST_CHECK_GT(bsiftPtr->getDescriptors().rows, 0);
        BOOST_CHECK_EQUAL(bsiftPtr->getBsift().size(), img->getDescriptors().rows);

        auto transformedBSIFTDatabase = descriptorMedianBSIFTExtractor
                .getDatabaseTranslatorPtr()->transformDatabase(vocabulary, bsiftDatabase);

        BOOST_REQUIRE(transformedBSIFTDatabase != nullptr);
        BOOST_CHECK_EQUAL(transformedBSIFTDatabase->getImages().size(), 1);
        BOOST_CHECK_EQUAL(transformedBSIFTDatabase->getCategories().size(), 0);

        auto transformedBSIFTImage = std::dynamic_pointer_cast<DescriptorMedianBSIFTExtractor::ImageBSIFT>(
                transformedBSIFTDatabase->getImages()[0]);

        BOOST_REQUIRE(transformedBSIFTImage != nullptr);
        BOOST_CHECK_GT(transformedBSIFTImage->getMatches().size(), 0);
        BOOST_CHECK_EQUAL(transformedBSIFTImage->getDescriptors().rows, 0);
        BOOST_CHECK_EQUAL(transformedBSIFTImage->getBsift().size(), img->getDescriptors().rows);
    }

BOOST_AUTO_TEST_SUITE_END()