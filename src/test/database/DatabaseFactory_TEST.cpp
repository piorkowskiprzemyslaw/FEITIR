//
// Created by Przemek Piórkowski on 11.03.2016.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE FEITR_DatabaseFactory test

#include <iostream>
#include "test_global.h"
#include <list>
#include <boost/test/unit_test.hpp>
#include "src/main/database/DatabaseFactory.h"

using namespace feitir;

struct DatabaseFixture {
    const DatabaseFactory databaseFactory;
    const ImageFactory imageFactory;
    const std::string databaseRes;
    const std::string firstRoot;
    const std::string secondRoot;
    const std::string thirdRoot;
    const std::string fourthRoot;
    const std::string fifthRoot;
    unsigned counter;

    DatabaseFixture() : databaseRes{resourcesRootDir() + "database/"},
                        firstRoot{"dir1/"}, secondRoot{"dir2/"}, thirdRoot{"dir3/"},
                        fourthRoot{"dir4/"}, fifthRoot{"dir5/"} {

    }

    void imagesDataClear(const DatabasePtr& db) {
#if TEST_HOUSEKEEPING
        for(auto& c : db->getCategories()) {
            for (auto& img : c->getImages()) {
                imageFactory.deleteImageData(img);
            }
        }

        for(auto& img : db->getImages()) {
            imageFactory.deleteImageData(img);
        }
#endif
    }
};

BOOST_FIXTURE_TEST_SUITE(DatabaseFactory_TEST, DatabaseFixture)

    BOOST_AUTO_TEST_CASE(FirstRootDatabase)
    {
        auto database = databaseFactory.createDatabase(databaseRes + firstRoot);
        BOOST_REQUIRE(database != nullptr);
        BOOST_CHECK_EQUAL(database->getRootPath(), databaseRes + firstRoot);
        BOOST_CHECK_EQUAL(database->getCategories().size(), 0);
        BOOST_CHECK_EQUAL(database->getImages().size(), 3);
        counter = 0;
        for (auto img : *database) {
            ++counter;
        }
        BOOST_CHECK_EQUAL(counter, 3);
        imagesDataClear(database);
    }

    BOOST_AUTO_TEST_CASE(FirstRootDatabaseNestedCategories)
    {
        auto database = databaseFactory.createDatabase(databaseRes + firstRoot, true);
        BOOST_REQUIRE(database != nullptr);
        BOOST_CHECK_EQUAL(database->getRootPath(), databaseRes + firstRoot);
        BOOST_CHECK_EQUAL(database->getCategories().size(), 0);
        BOOST_CHECK_EQUAL(database->getImages().size(), 3);
        counter = 0;
        for (auto img : *database) {
            ++counter;
        }
        BOOST_CHECK_EQUAL(counter, 3);
        imagesDataClear(database);
    }

    BOOST_AUTO_TEST_CASE(SecondRootDatabase)
    {
        auto database = databaseFactory.createDatabase(databaseRes + secondRoot);
        BOOST_REQUIRE(database != nullptr);
        BOOST_CHECK_EQUAL(database->getRootPath(), databaseRes + secondRoot);
        BOOST_CHECK_EQUAL(database->getCategories().size(), 2);
        BOOST_CHECK_EQUAL(database->getImages().size(), 1);
        counter = 0;
        for (auto img : *database) {
            ++counter;
        }
        BOOST_CHECK_EQUAL(counter, 7);
        BOOST_REQUIRE(database->getCategoryByName("dir2_1") != nullptr);
        BOOST_REQUIRE(database->getCategoryByName("dir2_2") != nullptr);
        BOOST_REQUIRE(database->getCategoryByName("dir2_3") == nullptr);
        imagesDataClear(database);
    }

    BOOST_AUTO_TEST_CASE(SecondRootDatabaseNestedCategories)
    {
        auto database = databaseFactory.createDatabase(databaseRes + secondRoot, true);
        BOOST_REQUIRE(database != nullptr);
        BOOST_CHECK_EQUAL(database->getRootPath(), databaseRes + secondRoot);
        BOOST_CHECK_EQUAL(database->getCategories().size(), 2);
        BOOST_CHECK_EQUAL(database->getImages().size(), 1);
        counter = 0;
        for (auto img : *database) {
            ++counter;
        }
        BOOST_CHECK_EQUAL(counter, 7);
        imagesDataClear(database);
    }

    BOOST_AUTO_TEST_CASE(ThirdRootDatabase)
    {
        auto database = databaseFactory.createDatabase(databaseRes + thirdRoot);
        BOOST_REQUIRE(database != nullptr);
        BOOST_CHECK_EQUAL(database->getRootPath(), databaseRes + thirdRoot);
        BOOST_CHECK_EQUAL(database->getCategories().size(), 2);
        BOOST_CHECK_EQUAL(database->getImages().size(), 1);
        counter = 0;
        for (auto img : *database) {
            ++counter;
        }
        BOOST_CHECK_EQUAL(counter, 11);
        imagesDataClear(database);
    }

    BOOST_AUTO_TEST_CASE(ThridRootDatabaseNestedCategories)
    {
        auto database = databaseFactory.createDatabase(databaseRes + thirdRoot, true);
        BOOST_REQUIRE(database != nullptr);
        BOOST_CHECK_EQUAL(database->getRootPath(), databaseRes + thirdRoot);
        BOOST_CHECK_EQUAL(database->getCategories().size(), 4);
        BOOST_CHECK_EQUAL(database->getImages().size(), 1);
        counter = 0;
        for (auto img : *database) {
            ++counter;
        }
        BOOST_CHECK_EQUAL(counter, 11);
        imagesDataClear(database);
    }

    BOOST_AUTO_TEST_CASE(FourthRootDatabase)
    {
        auto database = databaseFactory.createDatabase(databaseRes + fourthRoot, false);
        BOOST_REQUIRE(database != nullptr);
        BOOST_CHECK_EQUAL(database->getRootPath(), databaseRes + fourthRoot);
        BOOST_CHECK_EQUAL(database->getCategories().size(), 2);
        BOOST_CHECK_EQUAL(database->getImages().size(), 0);
        counter = 0;
        for (const auto & img : *database) {
            ++counter;
        }

        BOOST_CHECK_EQUAL(counter, 6);
        imagesDataClear(database);
    }

    BOOST_AUTO_TEST_CASE(FifthRootDatabase)
    {
        auto database = databaseFactory.createDatabase(databaseRes + fifthRoot, false);
        BOOST_REQUIRE(database != nullptr);
        BOOST_CHECK_EQUAL(database->getRootPath(), databaseRes + fifthRoot);
        BOOST_CHECK_EQUAL(database->getCategories().size(), 0);
        BOOST_CHECK_EQUAL(database->getImages().size(), 0);
        counter = 0;
        for (const auto & img : *database) {
            ++counter;
        }
        BOOST_CHECK_EQUAL(counter, 0);
        imagesDataClear(database);
    }

BOOST_AUTO_TEST_SUITE_END()