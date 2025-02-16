#include "catch.hpp"

#include "wordbank.h"

TEST_CASE("example wordbank test", "[wordbank]") {
    wordbank_ wb;

    REQUIRE(true);
}

TEST_CASE("test wordbank construct", "[wordbank]") {
    wordbank_ wb;
    wb.construct("tempdictionary.txt");

    REQUIRE(wb.contains_word("the"));
    REQUIRE(wb.contains_word("and"));
    REQUIRE(wb.contains_word("for"));
    REQUIRE(wb.contains_word("that"));
    REQUIRE(wb.contains_word("this"));
    REQUIRE(wb.contains_word("with"));
    REQUIRE(wb.contains_word("you"));
    REQUIRE(wb.contains_word("not"));
    REQUIRE(wb.contains_word("are"));
    REQUIRE(wb.contains_word("from"));
}

TEST_CASE("test wordbank no 1 or 2 letter words", "[wordbank]") {
    wordbank_ wb;
    wb.construct("tempdictionary.txt");

    REQUIRE_FALSE(wb.contains_word("i"));
    REQUIRE_FALSE(wb.contains_word("a"));
    REQUIRE_FALSE(wb.contains_word("is"));
    REQUIRE_FALSE(wb.contains_word("be"));
    REQUIRE_FALSE(wb.contains_word("do"));
    REQUIRE_FALSE(wb.contains_word("if"));
    REQUIRE_FALSE(wb.contains_word("my"));
    REQUIRE_FALSE(wb.contains_word("to"));
    REQUIRE_FALSE(wb.contains_word("he"));
    REQUIRE_FALSE(wb.contains_word("no"));
}

/// TODO: Add more tests for wordbank
// Convert word <-> code
// Convert char <-> code
// Get existing chars
// Get punc chars
