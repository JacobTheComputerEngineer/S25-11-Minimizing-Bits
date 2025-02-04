#include "catch.hpp"

#include "preprocessor.h"

TEST_CASE("example preprocessor test", "[preprocessor]") {
    preprocessor_ pre;

    pre.preprocessorTestbench("preprocessorTestFile.txt");

    REQUIRE(true);
}

// TODO: Add more tests

// TODO: Convert preprocessorTestBench() function to Catch-based tests
