#include "catch.hpp"
#include "decoder.h"
#include <fstream>

// Utility function to write test data (clears file first)
void writeTestData(const std::vector<uint8_t>& data) {
    std::ofstream file("decoderBtest.erl", std::ios::binary | std::ios::trunc); // TRUNC clears previous contents
    REQUIRE(file.is_open());  // Ensure file opens successfully
    file.write(reinterpret_cast<const char*>(data.data()), data.size());
    file.close();
}

TEST_CASE("Decoder - Read Next Bit", "[decoder]") {
    decoder_ dec;

    // Write a test byte: 0b10101011 (0xAB)
    writeTestData({0xAB});

    std::ifstream file("decoderBtest.erl", std::ios::binary);
    REQUIRE(file.is_open());

    bool bit;
    REQUIRE(dec.readNextBit(file, bit) == true);
    REQUIRE(bit == 1);
    REQUIRE(dec.readNextBit(file, bit) == true);
    REQUIRE(bit == 0);
    REQUIRE(dec.readNextBit(file, bit) == true);
    REQUIRE(bit == 1);
    REQUIRE(dec.readNextBit(file, bit) == true);
    REQUIRE(bit == 0);
    REQUIRE(dec.readNextBit(file, bit) == true);
    REQUIRE(bit == 1);
    REQUIRE(dec.readNextBit(file, bit) == true);
    REQUIRE(bit == 0);
    REQUIRE(dec.readNextBit(file, bit) == true);
    REQUIRE(bit == 1);
    REQUIRE(dec.readNextBit(file, bit) == true);
    REQUIRE(bit == 1);
    
    // No more bits should be available
    REQUIRE(dec.readNextBit(file, bit) == false);
    
    file.close();
}

TEST_CASE("Decoder - Read 13-bit Word", "[decoder]") {
    decoder_ dec;

    // Write a test word: 0b1010110000011010 (0xAC1A)
    writeTestData({0xAC, 0x1A});

    std::ifstream file("decoderBtest.erl", std::ios::binary);
    REQUIRE(file.is_open());

    bit_code_13_ wordBits;
    REQUIRE(dec.readBits(file, 13, wordBits) == true);
    REQUIRE(wordBits.to_ulong() == 0b1010110000011); // Only the first 13 bits should be read

    file.close();
}

TEST_CASE("Decoder - Read 6-bit Character", "[decoder]") {
    decoder_ dec;

    // Write a test byte: 0b11001100 (0xCC)
    writeTestData({0xCC});

    std::ifstream file("decoderBtest.erl", std::ios::binary);
    REQUIRE(file.is_open());

    bit_code_6_ charBits;
    REQUIRE(dec.readBits(file, 6, charBits) == true);
    REQUIRE(charBits.to_ulong() == 0b110011); // Only the first 6 bits should be read //failed

    file.close();
}
