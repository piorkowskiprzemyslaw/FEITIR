//
// Created by Przemek Piórkowski on 26.02.2016.
//
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE "FEITR_main"

#include <boost/test/unit_test.hpp>
#include <iostream>

BOOST_AUTO_TEST_SUITE(count_luck_TEST)

    BOOST_AUTO_TEST_CASE(First)
    {
        BOOST_CHECK_EQUAL(true, true);
    }

    BOOST_AUTO_TEST_CASE(Second)
    {
        BOOST_CHECK_EQUAL(false, false);
    }

BOOST_AUTO_TEST_SUITE_END()