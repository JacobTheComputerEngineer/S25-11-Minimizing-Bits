#include "catch.hpp"

#include "encoder.h"

TEST_CASE("example encoder test", "[encoder]") {
    encoder_ enc;

    REQUIRE(true);
}

TEST_CASE("encoder word test 1", "[encoder]") {
    encoder_ enc;
    std::bitset<8> readbits;

    REQUIRE(true);

    bit_code_13_ testcode1{ "0110100101110" };
    bit_code_13_ testflush{ "0000000000000" };

    std::ofstream clear("encodertest1.erl", std::ios::out | std::ios::trunc);
    clear.close();
    enc.printWord(testcode1, "encodertest1.erl");
    enc.printWord(testflush, "encodertest1.erl");
    std::ifstream read("encodertest1.erl", std::ios::binary);
    unsigned long n;
    read.read(reinterpret_cast<char*>(&n), sizeof(n));
    readbits = n;

    REQUIRE(!readbits.test(7));
    for (int i = 6; i >= 0; i--)
    {
        REQUIRE(readbits.test(i) == testcode1.test(i + 6));
    }
    read.read(reinterpret_cast<char*>(&n), sizeof(n));
    readbits = n;

    for (std::size_t i = 7; i >= 2; i--)
    {
        REQUIRE(readbits.test(i) == testcode1.test(i - 2));
    }
}

TEST_CASE("encoder word test 2", "[encoder]") {
    encoder_ enc;
    std::bitset<8> readbits;

    REQUIRE(true);

    bit_code_13_ testcode1{ "0001001110001" };
    bit_code_13_ testflush{ "0000000000000" };

    std::ofstream clear("encodertest1.erl", std::ios::out | std::ios::trunc);
    clear.close();
    enc.printWord(testcode1, "encodertest1.erl");
    enc.printWord(testflush, "encodertest1.erl");
    std::ifstream read("encodertest1.erl", std::ios::binary);
    unsigned long n;
    read.read(reinterpret_cast<char*>(&n), sizeof(n));
    readbits = n;

    REQUIRE(!readbits.test(7));
    for (int i = 6; i >= 0; i--)
    {
        REQUIRE(readbits.test(i) == testcode1.test(i + 6));
    }
    read.read(reinterpret_cast<char*>(&n), sizeof(n));
    readbits = n;

    for (std::size_t i = 7; i >= 2; i--)
    {
        REQUIRE(readbits.test(i) == testcode1.test(i - 2));
    }
}

TEST_CASE("encoder word test 3", "[encoder]") {
    encoder_ enc;
    std::bitset<8> readbits;

    REQUIRE(true);

    bit_code_13_ testcode1{ "1110100010110" };
    bit_code_13_ testflush{ "0000000000000" };

    std::ofstream clear("encodertest1.erl", std::ios::out | std::ios::trunc);
    clear.close();
    enc.printWord(testcode1, "encodertest1.erl");
    enc.printWord(testflush, "encodertest1.erl");
    std::ifstream read("encodertest1.erl", std::ios::binary);
    unsigned long n;
    read.read(reinterpret_cast<char*>(&n), sizeof(n));
    readbits = n;

    REQUIRE(!readbits.test(7));
    for (int i = 6; i >= 0; i--)
    {
        REQUIRE(readbits.test(i) == testcode1.test(i + 6));
    }
    read.read(reinterpret_cast<char*>(&n), sizeof(n));
    readbits = n;

    for (std::size_t i = 7; i >= 2; i--)
    {
        REQUIRE(readbits.test(i) == testcode1.test(i - 2));
    }
}

TEST_CASE("encoder word test 4", "[encoder]") {
    encoder_ enc;
    std::bitset<8> readbits;

    REQUIRE(true);

    bit_code_13_ testcode1{ "1101001010111" };
    bit_code_13_ testflush{ "0000000000000" };

    std::ofstream clear("encodertest1.erl", std::ios::out | std::ios::trunc);
    clear.close();
    enc.printWord(testcode1, "encodertest1.erl");
    enc.printWord(testflush, "encodertest1.erl");
    std::ifstream read("encodertest1.erl", std::ios::binary);
    unsigned long n;
    read.read(reinterpret_cast<char*>(&n), sizeof(n));
    readbits = n;

    REQUIRE(!readbits.test(7));
    for (int i = 6; i >= 0; i--)
    {
        REQUIRE(readbits.test(i) == testcode1.test(i + 6));
    }
    read.read(reinterpret_cast<char*>(&n), sizeof(n));
    readbits = n;

    for (std::size_t i = 7; i >= 2; i--)
    {
        REQUIRE(readbits.test(i) == testcode1.test(i - 2));
    }
}

TEST_CASE("encoder character test 1", "[encoder]") {
    encoder_ enc;
    std::bitset<8> readbits;

    REQUIRE(true);

    bit_code_6_ testcode1{ "011010" };
    bit_code_13_ testflush{ "0000000000000" };

    std::ofstream clear("encodertest1.erl", std::ios::out | std::ios::trunc);
    clear.close();
    enc.printCharacter(testcode1, "encodertest1.erl");
    enc.printWord(testflush, "encodertest1.erl");
    std::ifstream read("encodertest1.erl", std::ios::binary);
    unsigned long n;
    read.read(reinterpret_cast<char*>(&n), sizeof(n));
    readbits = n;

    REQUIRE(readbits.test(7));
    for (int i = 6; i >= 1; i--)
    {
        REQUIRE(readbits.test(i) == testcode1.test(i - 1));
    }
    REQUIRE(!readbits.test(0));
}

TEST_CASE("encoder character test 2", "[encoder]") {
    encoder_ enc;
    std::bitset<8> readbits;

    REQUIRE(true);

    bit_code_6_ testcode1{ "001001" };
    bit_code_13_ testflush{ "0000000000000" };

    std::ofstream clear("encodertest1.erl", std::ios::out | std::ios::trunc);
    clear.close();
    enc.printCharacter(testcode1, "encodertest1.erl");
    enc.printWord(testflush, "encodertest1.erl");
    std::ifstream read("encodertest1.erl", std::ios::binary);
    unsigned long n;
    read.read(reinterpret_cast<char*>(&n), sizeof(n));
    readbits = n;

    REQUIRE(readbits.test(7));
    for (int i = 6; i >= 1; i--)
    {
        REQUIRE(readbits.test(i) == testcode1.test(i - 1));
    }
    REQUIRE(!readbits.test(0));
}

TEST_CASE("encoder character test 3", "[encoder]") {
    encoder_ enc;
    std::bitset<8> readbits;

    REQUIRE(true);

    bit_code_6_ testcode1{ "111100" };
    bit_code_13_ testflush{ "0000000000000" };

    std::ofstream clear("encodertest1.erl", std::ios::out | std::ios::trunc);
    clear.close();
    enc.printCharacter(testcode1, "encodertest1.erl");
    enc.printWord(testflush, "encodertest1.erl");
    std::ifstream read("encodertest1.erl", std::ios::binary);
    unsigned long n;
    read.read(reinterpret_cast<char*>(&n), sizeof(n));
    readbits = n;

    REQUIRE(readbits.test(7));
    for (int i = 6; i >= 1; i--)
    {
        REQUIRE(readbits.test(i) == testcode1.test(i - 1));
    }
    REQUIRE(!readbits.test(0));
}

TEST_CASE("encoder character test 4", "[encoder]") {
    encoder_ enc;
    std::bitset<8> readbits;

    REQUIRE(true);

    bit_code_6_ testcode1{ "101011" };
    bit_code_13_ testflush{ "0000000000000" };

    std::ofstream clear("encodertest1.erl", std::ios::out | std::ios::trunc);
    clear.close();
    enc.printCharacter(testcode1, "encodertest1.erl");
    enc.printWord(testflush, "encodertest1.erl");
    std::ifstream read("encodertest1.erl", std::ios::binary);
    unsigned long n;
    read.read(reinterpret_cast<char*>(&n), sizeof(n));
    readbits = n;

    REQUIRE(readbits.test(7));
    for (int i = 6; i >= 1; i--)
    {
        REQUIRE(readbits.test(i) == testcode1.test(i - 1));
    }
    REQUIRE(!readbits.test(0));
}

TEST_CASE("mixed extensive test", "[encoder]") {
    encoder_ enc;
    std::bitset<8> readbits;

    bit_code_13_ testword1{ "0010110100000" };
    bit_code_13_ testword2{ "0000110111101" };
    bit_code_13_ testword3{ "1100011101100" };
    bit_code_13_ testword4{ "1110111001111" };
    bit_code_6_ testchar1{ "000010" };
    bit_code_6_ testchar2{ "001011" };
    bit_code_6_ testchar3{ "101010" };
    bit_code_6_ testchar4{ "110101" };
    bit_code_13_ testflush{ "0000000000000" };

    std::ofstream clear("encodertestmixed.erl", std::ios::out | std::ios::trunc);
    clear.close();
    enc.printWord(testword1, "encodertestmixed.erl");
    enc.printCharacter(testchar1, "encodertestmixed.erl");
    enc.printWord(testword2, "encodertestmixed.erl");
    enc.printCharacter(testchar2, "encodertestmixed.erl");
    enc.printWord(testword3, "encodertestmixed.erl");
    enc.printCharacter(testchar3, "encodertestmixed.erl");
    enc.printWord(testword4, "encodertestmixed.erl");
    enc.printCharacter(testchar4, "encodertestmixed.erl");
    enc.printWord(testflush, "encodertestmixed.erl");
    std::ifstream read("encodertestmixed.erl", std::ios::binary);
    unsigned long n;

    read.read(reinterpret_cast<char*>(&n), sizeof(n));
    readbits = n;
    REQUIRE(!readbits.test(7));
    for (int i = 6; i >= 0; i--)
    {
        REQUIRE(readbits.test(i) == testword1.test(i + 6));
    }

    read.read(reinterpret_cast<char*>(&n), sizeof(n));
    readbits = n;
    for (int i = 7; i >= 2; i--)
    {
        REQUIRE(readbits.test(i) == testword1.test(i - 2));
    }
    REQUIRE(readbits.test(1));
    REQUIRE(readbits.test(0) == testchar1.test(5));

    read.read(reinterpret_cast<char*>(&n), sizeof(n));
    readbits = n;
    for (int i = 7; i >= 3; i--)
    {
        REQUIRE(readbits.test(i) == testchar1.test(i - 3));
    }
    REQUIRE(!readbits.test(2));
    REQUIRE(readbits.test(1) == testword2.test(12));
    REQUIRE(readbits.test(0) == testword2.test(11));
    
    read.read(reinterpret_cast<char*>(&n), sizeof(n));
    readbits = n;
    for (int i = 7; i >= 0; i--)
    {
        REQUIRE(readbits.test(i) == testword2.test(i + 3));
    }

    read.read(reinterpret_cast<char*>(&n), sizeof(n));
    readbits = n;
    for (int i = 7; i >= 5; i--)
    {
        REQUIRE(readbits.test(i) == testword2.test(i - 5));
    }
    REQUIRE(readbits.test(4));
    for (int i = 3; i >= 0; i--)
    {
        REQUIRE(readbits.test(i) == testchar2.test(i + 2));
    }
    
    read.read(reinterpret_cast<char*>(&n), sizeof(n));
    readbits = n;
    REQUIRE(readbits.test(7) == testchar2.test(1));
    REQUIRE(readbits.test(6) == testchar2.test(0));
    REQUIRE(!readbits.test(5));
    for (int i = 4; i >= 0; i--)
    {
        REQUIRE(readbits.test(i) == testword3.test(i + 8));
    }

    read.read(reinterpret_cast<char*>(&n), sizeof(n));
    readbits = n;
    for (int i = 7; i >= 0; i--)
    {
        REQUIRE(readbits.test(i) == testword3.test(i));
    }

    read.read(reinterpret_cast<char*>(&n), sizeof(n));
    readbits = n;
    REQUIRE(readbits.test(7));
    for (int i = 6; i >= 1; i--)
    {
        REQUIRE(readbits.test(i) == testchar3.test(i - 1));
    }
    REQUIRE(!readbits.test(0));

    read.read(reinterpret_cast<char*>(&n), sizeof(n));
    readbits = n;
    for (int i = 7; i >= 0; i--)
    {
        REQUIRE(readbits.test(i) == testword4.test(i + 5));
    }

    read.read(reinterpret_cast<char*>(&n), sizeof(n));
    readbits = n;
    for (int i = 7; i >= 3; i--)
    {
        REQUIRE(readbits.test(i) == testword4.test(i - 3));
    }
    REQUIRE(readbits.test(2));
    REQUIRE(readbits.test(1) == testchar4.test(5));
    REQUIRE(readbits.test(0) == testchar4.test(4));

    read.read(reinterpret_cast<char*>(&n), sizeof(n));
    readbits = n;
    for (int i = 7; i >= 4; i--)
    {
        REQUIRE(readbits.test(i) == testchar4.test(i - 4));
    }
    for (int i = 3; i >= 0; i--)
    {
        REQUIRE(!readbits.test(i));
    }
}
