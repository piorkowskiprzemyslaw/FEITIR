//
// Created by Przemek Piórkowski on 20.03.2016.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE FEITR_KMeansVocabulary_test

#include <iostream>
#include "test_global.h"
#include <boost/test/unit_test.hpp>
#include <boost/filesystem.hpp>
#include <src/main/algorithm/BSIFT/descriptor_median/DescriptorMedianBSIFTExtractor.h>
#include "src/main/algorithm/vocabulary/kmeans/KMeansVocabularyBuilder.h"
#include "src/main/database/image/ImageFactory.h"

using namespace feitir;

struct KMeansFixture {
    const DatabaseFactory databaseFactory;
    const ImageFactory imageFactory;
    const std::string resourcesPath;
    const std::string imageName;
    const std::string vocabularyFile;
    const int means;

    KMeansFixture() : resourcesPath{resourcesRootDir() + "database/image/"},
                      imageName{"Lenna.png"},
                      vocabularyFile{"vocabulary.yml"},
                      means{5} {

    }

    ~KMeansFixture() {
        boost::filesystem::remove(resourcesPath + vocabularyFile);
    }

    void imagesDataClear(const ImagePtr& image) {
        imageFactory.deleteImageData(image);
    }
};

BOOST_FIXTURE_TEST_SUITE(KMeansVocabulary_TEST, KMeansFixture)

    BOOST_AUTO_TEST_CASE(Build)
    {
        auto img = imageFactory.createImage(resourcesPath + imageName);
        BOOST_REQUIRE(img != nullptr);
        KMeansVocabularyBuilder kMeansVocabularyBuilder;
        KMeansParameterPtr param = std::make_shared<KMeansParameter>(img->getDescriptors(), means);
        auto vocabulary = kMeansVocabularyBuilder.build(param);
        BOOST_REQUIRE_EQUAL(vocabulary->getVocabularyMatrix().rows, means);
        imagesDataClear(img);
    }

    BOOST_AUTO_TEST_CASE(SaveVocabularyToFile)
    {
        auto img = imageFactory.createImage(resourcesPath + imageName);
        BOOST_REQUIRE(img != nullptr);
        KMeansVocabularyBuilder kMeansVocabularyBuilder;
        KMeansParameterPtr param = std::make_shared<KMeansParameter>(img->getDescriptors(), means);
        auto vocabulary = kMeansVocabularyBuilder.build(param);
        kMeansVocabularyBuilder.saveToFile(vocabulary, resourcesPath + vocabularyFile);
        BOOST_REQUIRE(boost::filesystem::exists(resourcesPath + vocabularyFile));

        auto vocabularyFromFile = kMeansVocabularyBuilder.readFromFile(resourcesPath + vocabularyFile);

        BOOST_REQUIRE(cv::countNonZero(vocabulary->getVocabularyMatrix() != vocabularyFromFile->getVocabularyMatrix()) == 0);

        imagesDataClear(img);
    }

//    BOOST_AUTO_TEST_CASE(TransformBSIFTDatabaseWithVocabulary)
//    {
//        const DatabasePtr database = databaseFactory.createDatabase(resourcesPath);
//
//        BOOST_REQUIRE(database != nullptr);
//        BOOST_CHECK_EQUAL(database->getImages().size(), 1);
//        BOOST_CHECK_EQUAL(database->getCategories().size(), 0);
//
//        auto img = database->getImages()[0];
//
//        BOOST_REQUIRE(img != nullptr);
//        BOOST_CHECK_EQUAL(img->getMatches().size(), 0);
//        BOOST_CHECK_GT(img->getDescriptors().rows, 0);
//
//        KMeansVocabularyBuilder kMeansVocabularyBuilder;
//        KMeansParameterPtr param = std::make_shared<KMeansParameter>(img->getDescriptors(), means);
//        auto vocabulary = kMeansVocabularyBuilder.build(param);
//
//        DescriptorMedianBSIFTExtractor descriptorMedianBSIFTExtractor;
//        auto bsiftDatabase = descriptorMedianBSIFTExtractor.extractDatabaseBSIFT(database);
//
//        BOOST_REQUIRE(bsiftDatabase != nullptr);
//        BOOST_CHECK_EQUAL(bsiftDatabase->getImages().size(), 1);
//        BOOST_CHECK_EQUAL(bsiftDatabase->getCategories().size(), 0);
//
//        ImageBSIFTPtr bsiftPtr = std::dynamic_pointer_cast<ImageBSIFT>(bsiftDatabase->getImages()[0]);
//
//        BOOST_REQUIRE(bsiftPtr != nullptr);
//        BOOST_CHECK_EQUAL(bsiftPtr->getMatches().size(), 0);
//        BOOST_CHECK_GT(bsiftPtr->getDescriptors().rows, 0);
//        BOOST_CHECK_EQUAL(bsiftPtr->getBsift().size(), img->getDescriptors().rows);
//
//        auto transformedBSIFTDatabase = kMeansVocabularyBuilder.transformDatabase(vocabulary, bsiftDatabase);
//
//        BOOST_REQUIRE(transformedBSIFTDatabase != nullptr);
//        BOOST_CHECK_EQUAL(transformedBSIFTDatabase->getImages().size(), 1);
//        BOOST_CHECK_EQUAL(transformedBSIFTDatabase->getCategories().size(), 0);
//
//        auto transformedBSIFTImage = std::dynamic_pointer_cast<ImageBSIFT>(transformedBSIFTDatabase->getImages()[0]);
//
//        BOOST_REQUIRE(transformedBSIFTImage != nullptr);
//        BOOST_CHECK_GT(transformedBSIFTImage->getMatches().size(), 0);
//        BOOST_CHECK_EQUAL(transformedBSIFTImage->getDescriptors().rows, 0);
//        BOOST_CHECK_EQUAL(transformedBSIFTImage->getBsift().size(), img->getDescriptors().rows);
//    }

BOOST_AUTO_TEST_SUITE_END()