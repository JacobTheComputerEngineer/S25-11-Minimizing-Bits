#include "catch.hpp"

#include "wordbank.h"

TEST_CASE("example wordbank test", "[wordbank]") {
    wordbank_ wb;

    REQUIRE(true);
}

TEST_CASE("test wordbank construct", "[wordbank]") {
    wordbank_ wb;
    wb.construct("defaultdictionary.txt");

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
    wb.construct("defaultdictionary.txt");

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

TEST_CASE("convert word to code", "[wordbank]") {
    wordbank_ wb;
    wb.construct("defaultdictionary.txt");

    REQUIRE(wb.word_to_code("the") == bit_code_13_(0));
    REQUIRE(wb.word_to_code("and") == bit_code_13_(1));
    REQUIRE(wb.word_to_code("for") == bit_code_13_(2));
    REQUIRE(wb.word_to_code("that") == bit_code_13_(3));
    REQUIRE(wb.word_to_code("this") == bit_code_13_(4));
    REQUIRE(wb.word_to_code("with") == bit_code_13_(5));
    REQUIRE(wb.word_to_code("you") == bit_code_13_(6));
    REQUIRE(wb.word_to_code("not") == bit_code_13_(7));
    REQUIRE(wb.word_to_code("are") == bit_code_13_(8));
    REQUIRE(wb.word_to_code("from") == bit_code_13_(9));
}

TEST_CASE("convert code to word", "[wordbank]") {
    wordbank_ wb;
    wb.construct("defaultdictionary.txt");

    REQUIRE(wb.code_to_word(bit_code_13_(0)) == "the");
    REQUIRE(wb.code_to_word(bit_code_13_(1)) == "and");
    REQUIRE(wb.code_to_word(bit_code_13_(2)) == "for");
    REQUIRE(wb.code_to_word(bit_code_13_(3)) == "that");
    REQUIRE(wb.code_to_word(bit_code_13_(4)) == "this");
    REQUIRE(wb.code_to_word(bit_code_13_(5)) == "with");
    REQUIRE(wb.code_to_word(bit_code_13_(6)) == "you");
    REQUIRE(wb.code_to_word(bit_code_13_(7)) == "not");
    REQUIRE(wb.code_to_word(bit_code_13_(8)) == "are");
    REQUIRE(wb.code_to_word(bit_code_13_(9)) == "from");
}

/////

TEST_CASE("convert char to code", "[wordbank]") {
    wordbank_ wb;
    wb.construct("defaultdictionary.txt");

    REQUIRE(wb.char_to_code("a") == bit_code_6_(0));
    REQUIRE(wb.char_to_code("b") == bit_code_6_(1));
    REQUIRE(wb.char_to_code("c") == bit_code_6_(2));
    REQUIRE(wb.char_to_code("d") == bit_code_6_(3));
    REQUIRE(wb.char_to_code("e") == bit_code_6_(4));    
}

TEST_CASE("convert code to char", "[wordbank]") {
    wordbank_ wb;
    wb.construct("defaultdictionary.txt");

    REQUIRE(wb.code_to_char(bit_code_6_(0)) == "a");
    REQUIRE(wb.code_to_char(bit_code_6_(1)) == "b");
    REQUIRE(wb.code_to_char(bit_code_6_(2)) == "c");
    REQUIRE(wb.code_to_char(bit_code_6_(3)) == "d");
    REQUIRE(wb.code_to_char(bit_code_6_(4)) == "e");
}
