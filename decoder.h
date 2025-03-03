#ifndef DECODER_H
#define DECODER_H

#include <string>
#include <bitset>
#include <iostream>
#include <fstream>
#include "wordbank.h"

typedef std::bitset<13> bit_code_13_;
typedef std::bitset<6> bit_code_6_;

class decoder_
{
public:
    bool decodeFile(const std::string& inputFilename, const std::string& outputFilename);

private:
    bool readNextBit(std::ifstream &file, bool &bit);
    bool readBits(std::ifstream &file, int numBits, std::bitset<13> &bits);
    bool readBits(std::ifstream &file, int numBits, std::bitset<6> &bits);

    wordbank_ wb;
};

#endif // DECODER_H
