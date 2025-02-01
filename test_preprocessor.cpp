#include "catch.hpp"

#include "preprocessor.h"

TEST_CASE("test catch", "[preprocessor]") {
    REQUIRE(1 == 1);
    REQUIRE_FALSE(1 == 2);
}

TEST_CASE("test catch 2", "[preprocessor]") {
    std::cout << "This should fail" << std::endl;
    REQUIRE(false);
}