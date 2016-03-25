//
// Created by Przemek Piórkowski on 20.03.2016.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE FEITR_KMeansDictionary_test

#include <iostream>
#include "test_config_global.h"
#include <boost/test/unit_test.hpp>
#include "src/main/algorithm/vocabulary/KMeansVocabulary.h"
#include "src/main/database/image/ImageFactory.h"

using namespace feitir;

struct KMeansFixture {
    const ImageFactory imageFactory;
    const std::string resourcesPath;
    const std::string imageName;
    const int means;

    KMeansFixture() : resourcesPath{resourcesRootDir() + "database/image/"},
                      imageName{"Lenna.png"},
                      means{5} {

    }

    void imagesDataClear(const ImagePtr& image) {
        imageFactory.deleteImageData(image);
    }
};

BOOST_FIXTURE_TEST_SUITE(KMeansDictionary_TEST, KMeansFixture)

    BOOST_AUTO_TEST_CASE(FirstTestCase)
    {
        auto img = imageFactory.createImage(resourcesPath + imageName);
        KMeansVocabulary kMeans;
        cv::Mat vocabulary = kMeans.create(img->getDescriptors(), means);
        BOOST_REQUIRE_EQUAL(vocabulary.rows, means);
        imagesDataClear(img);
    }

BOOST_AUTO_TEST_SUITE_END()