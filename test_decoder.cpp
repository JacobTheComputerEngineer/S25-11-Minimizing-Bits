#include "catch.hpp"
#include "decoder.h"
#include <fstream>
#include <cstdio> // For std::remove

void clearTestFile() {
    std::remove("decoderBtest.erl"); // Delete the file if it exists
    std::ofstream file("decoderBtest.erl", std::ios::binary); // Recreate the file
    file.close();
}

// Utility function to write test data (clears file first)
void writeTestData(const std::vector<uint8_t>& data) {
    clearTestFile(); // Ensure file is cleared before writing
    std::ofstream file("decoderBtest.erl", std::ios::binary);
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



TEST_CASE("Decoder - Read Word, Char, Word", "[decoder]") {
    decoder_ dec;

    // Test data : word, char, word
    writeTestData({
        0x4C, 0x1A,  // (0b0100110000011 010) first 16 bits (1 word, half char)
        0xC9, 0xF3   // (0b110 0100111110011) second 16 bits (half char, 1 word)
    });

    std::ifstream file("decoderBtest.erl", std::ios::binary);
    REQUIRE(file.is_open());

    // Read first 13-bit word
    bit_code_13_ firstWord;
    REQUIRE(dec.readWordBits(file, firstWord) == true); // MV 3/25/25 - Edited readWordBits and readCharBits calls to reflect the reduced number of parameters
    REQUIRE(firstWord.to_ulong() == 0b0100110000011);

    // Read 6-bit character
    bit_code_6_ charBits;
    REQUIRE(dec.readCharBits(file, charBits) == true);
    REQUIRE(charBits.to_ulong() == 0b010110);

    // Read second 13-bit word
    bit_code_13_ secondWord;
    REQUIRE(dec.readWordBits(file, secondWord) == true);
    REQUIRE(secondWord.to_ulong() == 0b0100111110011);

    // Ensure no more bits
    bool bit;
    REQUIRE(dec.readNextBit(file, bit) == false);

    file.close();
}


// TEST_CASE("Decoder - Read 6-bit Character", "[decoder]") {
//     decoder_ dec;

//     // Write a test byte: 0b11001001 (0xC9)
//     writeTestData({0xC9});

//     std::ifstream file("decoderBtest.erl", std::ios::binary);
//     REQUIRE(file.is_open());

//     bit_code_6_ charBits;
//     REQUIRE(dec.readCharBits(file, 6, charBits) == true);
//     REQUIRE(charBits.to_ulong() == 0b110010); // Only the first 6 bits should be read //failed

//     file.close();
// }

// TEST_CASE("Decoder - Read 13-bit Word", "[decoder]") {
//     decoder_ dec;

//     // Write a test word: 0b1010110000011010 (0xAC1A)
//     writeTestData({0xAC, 0x1A});

//     std::ifstream file("decoderBtest.erl", std::ios::binary);
//     REQUIRE(file.is_open());

//     bit_code_13_ wordBits;
//     REQUIRE(dec.readWordBits(file, 13, wordBits) == true);
//     REQUIRE(wordBits.to_ulong() == 0b1010110000011); // Only the first 13 bits should be read

//     file.close();
// }



