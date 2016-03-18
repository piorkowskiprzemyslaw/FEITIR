//
// Created by Przemek Piórkowski on 14.03.2016.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE FEITR_CategoryFactory test

#include <iostream>
#include <list>
#include <boost/test/unit_test.hpp>
#include "src/main/database/category/CategoryFactory.h"

using namespace feitir;

struct CategoryFixture {
    const CategoryFactory categoryFactory;
    const std::string resourcesPath;
    const std::string firstRoot;
    const std::string secondRoot;
    const std::string thirdRoot;

    CategoryFixture() : resourcesPath{"/Users/Przemek/Development/ClionProjects/FEITIR/src/test/resources/database/"},
                        firstRoot{"dir1"}, secondRoot{"dir2"}, thirdRoot{"dir3"} {

    }
};

BOOST_FIXTURE_TEST_SUITE(CategoryFactory_TEST, CategoryFixture)

    BOOST_AUTO_TEST_CASE(FirstRootCategory)
    {
        auto category = categoryFactory.createCategory(resourcesPath, resourcesPath + firstRoot);
        BOOST_REQUIRE(category != nullptr);
        BOOST_CHECK_EQUAL(category->getPath(), resourcesPath + firstRoot);
        BOOST_CHECK_EQUAL(category->getName(), firstRoot);
        BOOST_CHECK_EQUAL(category->getImages().size(), 3);
    }

    BOOST_AUTO_TEST_CASE(FirstRootCategoryRecursive)
    {
        auto category = categoryFactory.createCategory(resourcesPath, resourcesPath + firstRoot, false);
        BOOST_REQUIRE(category != nullptr);
        BOOST_CHECK_EQUAL(category->getPath(), resourcesPath + firstRoot);
        BOOST_CHECK_EQUAL(category->getName(), firstRoot);
        BOOST_CHECK_EQUAL(category->getImages().size(), 3);
    }

    BOOST_AUTO_TEST_CASE(SecondRootCategory)
    {
        auto category = categoryFactory.createCategory(resourcesPath, resourcesPath + secondRoot);
        BOOST_REQUIRE(category != nullptr);
        BOOST_CHECK_EQUAL(category->getPath(), resourcesPath + secondRoot);
        BOOST_CHECK_EQUAL(category->getName(), secondRoot);
        BOOST_CHECK_EQUAL(category->getImages().size(), 7);
    }

    BOOST_AUTO_TEST_CASE(SecondRootCategoryRecursive)
    {
        auto category = categoryFactory.createCategory(resourcesPath, resourcesPath + secondRoot, false);
        BOOST_REQUIRE(category != nullptr);
        BOOST_CHECK_EQUAL(category->getPath(), resourcesPath + secondRoot);
        BOOST_CHECK_EQUAL(category->getName(), secondRoot);
        BOOST_CHECK_EQUAL(category->getImages().size(), 1);
    }

    BOOST_AUTO_TEST_CASE(ThirdRootCategory)
    {
        auto category = categoryFactory.createCategory(resourcesPath, resourcesPath + thirdRoot);
        BOOST_REQUIRE(category != nullptr);
        BOOST_CHECK_EQUAL(category->getPath(), resourcesPath + thirdRoot);
        BOOST_CHECK_EQUAL(category->getName(), thirdRoot);
        BOOST_CHECK_EQUAL(category->getImages().size(), 11);
    }

    BOOST_AUTO_TEST_CASE(ThirdRootCategoryRecursive)
    {
        auto category = categoryFactory.createCategory(resourcesPath, resourcesPath + thirdRoot, false);
        BOOST_REQUIRE(category != nullptr);
        BOOST_CHECK_EQUAL(category->getPath(), resourcesPath + thirdRoot);
        BOOST_CHECK_EQUAL(category->getName(), thirdRoot);
        BOOST_CHECK_EQUAL(category->getImages().size(), 1);
    }

BOOST_AUTO_TEST_SUITE_END()