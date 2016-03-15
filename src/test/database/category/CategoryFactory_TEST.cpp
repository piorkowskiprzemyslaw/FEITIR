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
        auto category = categoryFactory.createCategory(resourcesPath + firstRoot);
        BOOST_REQUIRE(category != nullptr);
    }

    BOOST_AUTO_TEST_CASE(FirstRootCategoryRecursive)
    {
        auto category = categoryFactory.createCategory(resourcesPath + firstRoot, false);
        BOOST_REQUIRE(category != nullptr);
    }

    BOOST_AUTO_TEST_CASE(SecondRootCategory)
    {
        auto category = categoryFactory.createCategory(resourcesPath + secondRoot);
        BOOST_REQUIRE(category != nullptr);
    }

    BOOST_AUTO_TEST_CASE(SecondRootCategoryRecursive)
    {
        auto category = categoryFactory.createCategory(resourcesPath + secondRoot, false);
        BOOST_REQUIRE(category != nullptr);
    }

    BOOST_AUTO_TEST_CASE(ThirdRootCategory)
    {
        auto category = categoryFactory.createCategory(resourcesPath + thirdRoot);
        BOOST_REQUIRE(category != nullptr);
    }

    BOOST_AUTO_TEST_CASE(ThirdRootCategoryRecursive)
    {
        auto category = categoryFactory.createCategory(resourcesPath + thirdRoot, false);
        BOOST_REQUIRE(category != nullptr);
    }

BOOST_AUTO_TEST_SUITE_END()