//
// Created by Przemek Piórkowski on 20.03.2016.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE FEITR_KMeansDictionary_test

#include <iostream>
#include <boost/test/unit_test.hpp>
#include "src/main/algorithm/dictionary/KMeansDictionary.h"
#include "src/main/database/image/ImageFactory.h"

using namespace feitir;

struct KMeansFixture {
    const ImageFactory imageFactory;
    const std::string resourcesPath;
    const std::string imageName;

    KMeansFixture() : resourcesPath{"/Users/Przemek/Development/ClionProjects/FEITIR/src/test/resources/database/image/"},
                        imageName{"Lenna.png"} {

    }

    void imagesDataClear(const ImagePtr& image) {
        imageFactory.deleteImageData(image);
    }
};

BOOST_FIXTURE_TEST_SUITE(KMeansDictionary_TEST, KMeansFixture)

    BOOST_AUTO_TEST_CASE(FirstTestCase)
    {
        ImageFactory imageFactory;
        auto img = imageFactory.createImage(resourcesPath + imageName);
        int MEANS = 5;
        KMeansDictionary dictionary;
        cv::Mat centers = dictionary.create(img->getDescriptors(), MEANS);
        BOOST_REQUIRE_EQUAL(centers.rows, MEANS);
        imagesDataClear(img);
    }

BOOST_AUTO_TEST_SUITE_END()