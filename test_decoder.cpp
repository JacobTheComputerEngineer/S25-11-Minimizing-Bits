#include "catch.hpp"

#include "decoder.h"
#include <fstream>
TEST_CASE("example decoder test", "[decoder]") {
    decoder_ dec;

    REQUIRE(true);
}

TEST_CASE("Decoder - Valid File Extensions", "[decoder]") {
    decoder_ dec;
    REQUIRE(dec.decodeFile("decoderBtest.erl", "decoderTtest.txt") == true);
}

TEST_CASE("Decoder - Invalid Input File Extension", "[decoder]") {
    decoder_ dec;
    REQUIRE(dec.decodeFile("test.bin", "decoderTtest.txt") == false); // Wrong input extension
}

TEST_CASE("Decoder - Invalid Output File Extension", "[decoder]") {
    decoder_ dec;
    REQUIRE(dec.decodeFile("decoderBtest.erl", "output.bin") == false); // Wrong output extension
}

TEST_CASE("Decoder - File Does Not Exist", "[decoder]") {
    decoder_ dec;
    REQUIRE(dec.decodeFile("nonexistent.erl", "decoderTtest.txt") == false);
}

TEST_CASE("Decoder - Basic Decoding", "[decoder]") {
    decoder_ dec;
    REQUIRE(dec.decodeFile("decoderBtest.erl", "decoderTtest.txt") == true);
    
    // Read the expected output from the text file
    std::ifstream file("decoderTtest.txt");
    std::string output((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    
    //still need to make an expected output. I am guessing we will check this in tandem with encoder
    REQUIRE(output == "expected_output");
}

TEST_CASE("Decoder - Handles Corrupt File", "[decoder]") {
    decoder_ dec;

    //still need to make a corrupted file version
    REQUIRE(dec.decodeFile("corrupt.erl", "decoderTtest.txt") == false);
}
