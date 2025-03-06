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
    bool readBits(std::ifstream &file, int numBits, std::bitset<13> &bits);
    bool readBits(std::ifstream &file, int numBits, std::bitset<6> &bits);
};
//bool hasExtension(const std::string& filename, const std::string& extension); //function may come back
#endif // DECODER_H
