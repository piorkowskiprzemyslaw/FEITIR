//
// Created by Przemek Piórkowski on 14.03.2016.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE FEITR_CategoryFactory test

#include <iostream>
#include "test_global.h"
#include <list>
#include <boost/test/unit_test.hpp>
#include "src/main/database/category/CategoryFactory.h"

using namespace feitir;

struct CategoryFixture {
    const CategoryFactory categoryFactory;
    const ImageFactory imageFactory;
    const std::string resourcesPath;
    const std::string firstRoot;
    const std::string secondRoot;
    const std::string thirdRoot;
    unsigned counter;

    CategoryFixture() : resourcesPath{resourcesRootDir() + "database/"},
                        firstRoot{"dir1"}, secondRoot{"dir2"}, thirdRoot{"dir3"} {

    }

    void imagesDataClear(const CategoryPtr& category) {
#if TEST_HOUSEKEEPING
        for (auto& img : category->getImages()) {
            imageFactory.deleteImageData(img);
        }
#endif
    }
};

BOOST_FIXTURE_TEST_SUITE(CategoryFactory_TEST, CategoryFixture)

    BOOST_AUTO_TEST_CASE(FirstRootCategory)
    {
        auto category = categoryFactory.createCategory(resourcesPath, resourcesPath + firstRoot);
        counter = 0;
        BOOST_REQUIRE(category != nullptr);
        BOOST_CHECK_EQUAL(category->getPath(), resourcesPath + firstRoot);
        BOOST_CHECK_EQUAL(category->getName(), firstRoot);
        BOOST_CHECK_EQUAL(category->getImages().size(), 3);

        for (auto img : *category) {
            ++counter;
        }
        BOOST_CHECK_EQUAL(counter, 3);
        imagesDataClear(category);
    }

    BOOST_AUTO_TEST_CASE(FirstRootCategoryRecursive)
    {
        auto category = categoryFactory.createCategory(resourcesPath, resourcesPath + firstRoot, false);
        counter = 0;
        BOOST_REQUIRE(category != nullptr);
        BOOST_CHECK_EQUAL(category->getPath(), resourcesPath + firstRoot);
        BOOST_CHECK_EQUAL(category->getName(), firstRoot);
        BOOST_CHECK_EQUAL(category->getImages().size(), 3);

        for (auto img : *category) {
            ++counter;
        }
        BOOST_CHECK_EQUAL(counter, 3);
        imagesDataClear(category);
    }

    BOOST_AUTO_TEST_CASE(SecondRootCategory)
    {
        auto category = categoryFactory.createCategory(resourcesPath, resourcesPath + secondRoot);
        counter = 0;
        BOOST_REQUIRE(category != nullptr);
        BOOST_CHECK_EQUAL(category->getPath(), resourcesPath + secondRoot);
        BOOST_CHECK_EQUAL(category->getName(), secondRoot);
        BOOST_CHECK_EQUAL(category->getImages().size(), 7);

        for (auto img : *category) {
            ++counter;
        }
        BOOST_CHECK_EQUAL(counter, 7);
        imagesDataClear(category);
    }

    BOOST_AUTO_TEST_CASE(SecondRootCategoryRecursive)
    {
        auto category = categoryFactory.createCategory(resourcesPath, resourcesPath + secondRoot, false);
        counter = 0;
        BOOST_REQUIRE(category != nullptr);
        BOOST_CHECK_EQUAL(category->getPath(), resourcesPath + secondRoot);
        BOOST_CHECK_EQUAL(category->getName(), secondRoot);
        BOOST_CHECK_EQUAL(category->getImages().size(), 1);

        for (auto img : *category) {
            ++counter;
        }
        BOOST_CHECK_EQUAL(counter, 1);
        imagesDataClear(category);
    }

    BOOST_AUTO_TEST_CASE(ThirdRootCategory)
    {
        auto category = categoryFactory.createCategory(resourcesPath, resourcesPath + thirdRoot);
        counter = 0;
        BOOST_REQUIRE(category != nullptr);
        BOOST_CHECK_EQUAL(category->getPath(), resourcesPath + thirdRoot);
        BOOST_CHECK_EQUAL(category->getName(), thirdRoot);
        BOOST_CHECK_EQUAL(category->getImages().size(), 11);

        for (auto img : *category) {
            ++counter;
        }
        BOOST_CHECK_EQUAL(counter, 11);
        imagesDataClear(category);
    }

    BOOST_AUTO_TEST_CASE(ThirdRootCategoryRecursive)
    {
        auto category = categoryFactory.createCategory(resourcesPath, resourcesPath + thirdRoot, false);
        counter = 0;
        BOOST_REQUIRE(category != nullptr);
        BOOST_CHECK_EQUAL(category->getPath(), resourcesPath + thirdRoot);
        BOOST_CHECK_EQUAL(category->getName(), thirdRoot);
        BOOST_CHECK_EQUAL(category->getImages().size(), 1);

        for (auto img : *category) {
            ++counter;
        }
        BOOST_CHECK_EQUAL(counter, 1);
        imagesDataClear(category);
    }

BOOST_AUTO_TEST_SUITE_END()