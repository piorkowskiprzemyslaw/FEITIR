//
// Created by Przemek Piórkowski on 29.02.2016.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE FEITR_ImageFactory test

#include <iostream>
#include "test_config_global.h"
#include <boost/test/unit_test.hpp>
#include <src/main/database/image/ImageFactory.h>
#include <opencv2/opencv.hpp>
#include <src/main/algorithm/vocabulary/KMeansVocabulary.h>

typedef cv::xfeatures2d::SIFT SIFT;
using namespace feitir;

struct ImageFixture {
    const KMeansVocabulary vocabularyBuilder;
    const ImageFactory imageFactory;
    const std::string imgName;
    const std::string resourcePath;
    const std::string vocabularyFileName;
    const std::string keyPointsFilePath;
    const cv::Mat image;
    std::vector<cv::KeyPoint> keyPoints;
    cv::Mat descriptors;

    ImageFixture() : resourcePath{resourcesRootDir() + "database/image/"},
                     imgName{"Lenna.png"},
                     vocabularyFileName{"vocabulary.yml"},
                     keyPointsFilePath{resourcePath + ImageFactory::IMAGE_DATA_FILE_PREFIX
                                       + "Lenna.png" + ImageFactory::IMAGE_DATA_FILE_POSTFIX},
                     image{cv::imread(resourcePath + imgName, CV_LOAD_IMAGE_UNCHANGED)} {
        cv::Ptr<SIFT> sift = SIFT::create();
        sift->detectAndCompute(image, cv::noArray(), keyPoints, descriptors);
    }

    ~ImageFixture() {
#if TEST_HOUSEKEEPING
        boost::filesystem::remove(keyPointsFilePath);
#endif
    }

    bool keyPointsEqual(const cv::KeyPoint & kp1, const cv::KeyPoint & kp2) const {
        return (kp1.size == kp2.size) && (kp1.angle == kp2.angle)
               && (kp1.class_id == kp2.class_id) && (kp1.octave == kp2.octave)
               && (kp1.response == kp2.response) && (kp1.pt == kp2.pt);
    }
};

BOOST_FIXTURE_TEST_SUITE(ImageFactory_TEST, ImageFixture)

    BOOST_AUTO_TEST_CASE(createImageFromScratch)
    {
        auto img = imageFactory.createImage(resourcePath + imgName);

        BOOST_CHECK_EQUAL(img->getFullPath(), resourcePath + imgName);
        BOOST_CHECK_EQUAL(img->getFileName(), imgName);
        BOOST_CHECK_EQUAL(img->getPath(), resourcePath);
        BOOST_CHECK(img->getExtension() == Extension::PNG);
        BOOST_REQUIRE_GT(img->getKeyPoints().size(), 0);
        BOOST_CHECK_EQUAL(img->getKeyPoints().size(), keyPoints.size());

        for (int i = 0; i < keyPoints.size(); ++i) {
            BOOST_CHECK(keyPointsEqual(img->getKeyPoints()[i], keyPoints[i]));
        }

        BOOST_CHECK(cv::countNonZero(descriptors != img->getDescriptors()) == 0);
    }

    BOOST_AUTO_TEST_CASE(createImageFromFiles)
    {
        auto img = imageFactory.createImage(resourcePath + imgName);
        imageFactory.saveImageData(img);

        BOOST_REQUIRE(boost::filesystem::exists(keyPointsFilePath));

        auto imgFromFile = imageFactory.createImage(resourcePath + imgName);
        BOOST_CHECK_EQUAL(imgFromFile->getFullPath(), resourcePath + imgName);
        BOOST_CHECK_EQUAL(imgFromFile->getFileName(), imgName);
        BOOST_CHECK_EQUAL(imgFromFile->getPath(), resourcePath);
        BOOST_CHECK(imgFromFile->getExtension() == Extension::PNG);
        BOOST_REQUIRE_GT(imgFromFile->getKeyPoints().size(), 0);
        BOOST_CHECK_EQUAL(imgFromFile->getKeyPoints().size(), keyPoints.size());

        for (int i = 0; i < keyPoints.size(); ++i) {
            BOOST_CHECK(keyPointsEqual(imgFromFile->getKeyPoints()[i], keyPoints[i]));
        }

        BOOST_CHECK(cv::countNonZero(descriptors != imgFromFile->getDescriptors()) == 0);
        BOOST_CHECK(imageFactory.deleteImageData(img));

        BOOST_REQUIRE(!boost::filesystem::exists(keyPointsFilePath));
    }


    BOOST_AUTO_TEST_CASE(unknownFileExtension)
    {
        auto img = imageFactory.createImage(resourcePath + "Lenna.txt");
        BOOST_REQUIRE(img == nullptr);
    }

    BOOST_AUTO_TEST_CASE(lackOfFileExtension)
    {
        auto img = imageFactory.createImage(resourcePath + "Lenna");
        BOOST_REQUIRE(img == nullptr);
    }

    BOOST_AUTO_TEST_CASE(noSuchFile)
    {
        auto img = imageFactory.createImage(resourcePath + "Lenna1");
        BOOST_REQUIRE(img == nullptr);
    }

    BOOST_AUTO_TEST_CASE(directory)
    {
        auto img = imageFactory.createImage(resourcePath);
        BOOST_REQUIRE(img == nullptr);
    }

    BOOST_AUTO_TEST_CASE(representAsVocabulary)
    {
        auto vocabulary = vocabularyBuilder.readFromFile(resourcePath + vocabularyFileName);
        auto img = imageFactory.createImage(resourcePath + imgName);
        BOOST_REQUIRE(img != nullptr);
        auto vocImage = imageFactory.representAsVocabulary(img, vocabulary);
        std::cout << resourcesRootDir() << std::endl;
        BOOST_REQUIRE(vocImage != nullptr);
    }

BOOST_AUTO_TEST_SUITE_END()