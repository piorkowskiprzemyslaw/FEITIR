//
// Created by Przemek Piórkowski on 18.04.2016.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE FEITR_HKMeansVocabulary_test

#include <iostream>
#include <cmath>
#include "test_global.h"
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>
#include "src/main/algorithm/BSIFT/descriptor_median/DescriptorMedianBSIFTExtractor.h"
#include "src/main/algorithm/vocabulary/hierarchical_kmeans/HKMeansVocabularyBuilder.h"
#include "src/main/database/DatabaseFactory.h"
#include "src/main/database/image/ImageFactory.h"

using namespace feitir;

struct HKMeansFixture {
    const DatabaseFactory databaseFactory;
    const ImageFactory imageFactory;
    const std::string resourcesPath;
    const std::string imageName;
    const std::string vocabularyFile;
    const int K;
    const int L;

    HKMeansFixture() : resourcesPath{resourcesRootDir() + "database/image/"},
                       imageName{"Lenna.png"},
                       vocabularyFile{"vocabulary.yml"},
                       K{2}, L{3} {

    }

    ~HKMeansFixture() {
        boost::filesystem::remove(resourcesPath + vocabularyFile);
    }

    void imagesDataClear(const ImagePtr& image) {
        imageFactory.deleteImageData(image);
    }
};

BOOST_FIXTURE_TEST_SUITE(HKMeansVocabulary_TEST, HKMeansFixture)

    BOOST_AUTO_TEST_CASE(Build)
    {
        auto img = imageFactory.createImage(resourcesPath + imageName);
        BOOST_REQUIRE(img != nullptr);
        HKMeansVocabularyBuilder builder;
        auto vocabulary = builder.build(std::make_shared<HKMeansParameter>(img->getDescriptors(), K, L));
        BOOST_REQUIRE_EQUAL(vocabulary->getVocabularyMatrix().rows, std::pow(K, L + 1));
        imagesDataClear(img);
    }

    BOOST_AUTO_TEST_CASE(SaveVocabularyToFile)
    {
        auto img = imageFactory.createImage(resourcesPath + imageName);
        BOOST_REQUIRE(img != nullptr);
        HKMeansVocabularyBuilder builder;
        auto vocabulary = builder.build(std::make_shared<HKMeansParameter>(img->getDescriptors(), K, L));
        builder.saveToFile(vocabulary, resourcesPath + vocabularyFile);
        BOOST_REQUIRE(boost::filesystem::exists(resourcesPath + vocabularyFile));
        auto vocabularyFromFile = builder.readFromFile(resourcesPath + vocabularyFile);

        BOOST_REQUIRE_EQUAL(cv::countNonZero(vocabulary->getVocabularyMatrix() != vocabularyFromFile->getVocabularyMatrix()), 0);
        BOOST_REQUIRE_EQUAL(vocabularyFromFile->getVocabularyMatrix().rows, std::pow(K, L + 1));
        BOOST_REQUIRE(*vocabulary == *vocabularyFromFile);

        imagesDataClear(img);
    }

BOOST_AUTO_TEST_SUITE_END()