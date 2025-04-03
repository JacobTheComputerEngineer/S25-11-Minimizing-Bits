#ifndef DECODER_H
#define DECODER_H

#include <string>
#include <bitset>
#include <iostream>
#include <fstream>

typedef std::bitset<13> bit_code_13_;
typedef std::bitset<6> bit_code_6_;

class decoder_
{
public:
    bool readNextBit(std::ifstream &file, bool &bit);
    bool readWordBits(std::ifstream &file, std::bitset<13> &bits);
    bool readCharBits(std::ifstream &file, std::bitset<6> &bits);
};
#endif // DECODER_H
