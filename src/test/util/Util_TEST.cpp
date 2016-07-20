//
// Created by Przemek Piórkowski on 15.07.2016.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE FEITR_Util_test

#include <iostream>
#include "test_global.h"
#include <boost/test/unit_test.hpp>
#include "src/main/util/Util.h"
#include <algorithm>

using namespace feitir;

BOOST_AUTO_TEST_SUITE(Util_TEST)

    BOOST_AUTO_TEST_CASE(generateAllSubsets_TEST)
    {
        std::set<unsigned> s1 = {0, 1, 2, 3, 4};
        auto subsets1 = Util::generateAllSubsets(s1, 1);
        BOOST_REQUIRE_EQUAL(subsets1.size(), 6);
        BOOST_REQUIRE(std::find(subsets1.begin(), subsets1.end(), std::set<unsigned>({})) != subsets1.end());
        BOOST_REQUIRE(std::find(subsets1.begin(), subsets1.end(), std::set<unsigned>({0})) != subsets1.end());
        BOOST_REQUIRE(std::find(subsets1.begin(), subsets1.end(), std::set<unsigned>({1})) != subsets1.end());
        BOOST_REQUIRE(std::find(subsets1.begin(), subsets1.end(), std::set<unsigned>({2})) != subsets1.end());
        BOOST_REQUIRE(std::find(subsets1.begin(), subsets1.end(), std::set<unsigned>({3})) != subsets1.end());
        BOOST_REQUIRE(std::find(subsets1.begin(), subsets1.end(), std::set<unsigned>({4})) != subsets1.end());

        std::set<unsigned> s2 = {0, 1, 2, 3};
        auto subsets2 = Util::generateAllSubsets(s2, 2);
        BOOST_REQUIRE_EQUAL(subsets2.size(), 6 + 4 + 1);
        BOOST_REQUIRE(std::find(subsets2.begin(), subsets2.end(), std::set<unsigned>({})) != subsets2.end());
        BOOST_REQUIRE(std::find(subsets2.begin(), subsets2.end(), std::set<unsigned>({0})) != subsets2.end());
        BOOST_REQUIRE(std::find(subsets2.begin(), subsets2.end(), std::set<unsigned>({1})) != subsets2.end());
        BOOST_REQUIRE(std::find(subsets2.begin(), subsets2.end(), std::set<unsigned>({2})) != subsets2.end());
        BOOST_REQUIRE(std::find(subsets2.begin(), subsets2.end(), std::set<unsigned>({3})) != subsets2.end());
        BOOST_REQUIRE(std::find(subsets2.begin(), subsets2.end(), std::set<unsigned>({0, 1})) != subsets2.end());
        BOOST_REQUIRE(std::find(subsets2.begin(), subsets2.end(), std::set<unsigned>({0, 2})) != subsets2.end());
        BOOST_REQUIRE(std::find(subsets2.begin(), subsets2.end(), std::set<unsigned>({0, 3})) != subsets2.end());
        BOOST_REQUIRE(std::find(subsets2.begin(), subsets2.end(), std::set<unsigned>({1, 2})) != subsets2.end());
        BOOST_REQUIRE(std::find(subsets2.begin(), subsets2.end(), std::set<unsigned>({1, 3})) != subsets2.end());
        BOOST_REQUIRE(std::find(subsets2.begin(), subsets2.end(), std::set<unsigned>({2, 3})) != subsets2.end());

    }

BOOST_AUTO_TEST_SUITE_END()