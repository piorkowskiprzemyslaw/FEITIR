//
// Created by Przemek Piórkowski on 04.04.2016.
//

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE FEITR_InvertedFileIndexer_test

#include <iostream>
#include "test_config_global.h"
#include <boost/test/unit_test.hpp>
#include "src/main/algorithm/indexer/inverted_file/InvertedFileIndexer.h"

using namespace feitir;

struct InvertedFileIndexerFixture {

    InvertedFileIndexerFixture()  {

    }
};

BOOST_FIXTURE_TEST_SUITE(InvertedFileIndexer_TEST, InvertedFileIndexerFixture)

    BOOST_AUTO_TEST_CASE(FirstTestCase)
    {
        BOOST_REQUIRE(true);
    }

BOOST_AUTO_TEST_SUITE_END()