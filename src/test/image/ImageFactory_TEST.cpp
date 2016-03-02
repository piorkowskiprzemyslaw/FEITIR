//
// Created by Przemek Piórkowski on 29.02.2016.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE FEITR_main test

#include <iostream>
#include <boost/test/unit_test.hpp>
#include <src/main/image/ImageFactory.h>

#include <opencv2/opencv.hpp>
#include <opencv2/xfeatures2d.hpp>

typedef cv::xfeatures2d::SIFT SIFT;

struct F {
    const std::string imgPath;
    const cv::Mat image;
    std::vector<cv::KeyPoint> keyPoints;

    F() : imgPath{"/Users/Przemek/Development/ClionProjects/FEITIR/src/test/resources/Lenna.png"},
        image{cv::imread(imgPath, CV_LOAD_IMAGE_UNCHANGED)} {
        cv::Ptr<SIFT> sift = SIFT::create();
        sift->detect(image, keyPoints);
    }

    ~F() {

    }

    bool keyPointsEqual(const cv::KeyPoint & kp1, const cv::KeyPoint & kp2) {
        return (kp1.size == kp2.size) && (kp1.angle == kp2.angle)
               && (kp1.class_id == kp2.class_id) && (kp1.octave == kp2.octave)
               && (kp1.response == kp2.response) && (kp1.pt == kp2.pt);
    }
};

using namespace feitir;

BOOST_FIXTURE_TEST_SUITE(ImageFactory_TEST, F)

    BOOST_AUTO_TEST_CASE(createImageTest)
    {
        ImageFactory imageFactory;
        std::shared_ptr<Image> img = imageFactory.createImage(imgPath);

        BOOST_CHECK_EQUAL(img->getPath(), imgPath);
        BOOST_CHECK_EQUAL(img->getName(), "Lenna.png");
        BOOST_CHECK(img->getExtension() == Extension::PNG);
        BOOST_REQUIRE_GT(img->getKeyPoints().size(), 0);
        BOOST_CHECK_EQUAL(img->getKeyPoints().size(), keyPoints.size());

        for (int i = 0; i < keyPoints.size(); ++i) {
            BOOST_CHECK(keyPointsEqual(img->getKeyPoints()[i], keyPoints[i]));
        }
    }

BOOST_AUTO_TEST_SUITE_END()