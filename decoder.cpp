#include "decoder.h"

//***function moved to main for now, could come back***
//function solely for checking file extension
// bool hasExtension(const std::string& filename, const std::string& extension) {
//     return filename.size() >= extension.size() &&
//            filename.compare(filename.size() - extension.size(), extension.size(), extension) == 0;
// }


//function reads next bit, and by reference updates the bit in decodeFile
//returns true if bit is read successfully 
bool decoder_::readNextBit(std::ifstream &file, bool &bit)
{
    static std::bitset<8> buffer; //contains the 8 pulled bits (set initially on the first call)
    static int index = -1; //ensures that the index is reset on the first function call
    
    if (index == -1) {//if done with byte, grab the next byte
        char byte;
        if (!file.read(&byte, 1)) return false; //error return false such as EOF
        buffer = std::bitset<8>(static_cast<unsigned char>(byte)); //8bit representation of pulled char
        index = 7;//reset index to 7 (MSB)
    }
    
    bit = buffer.test(index--); //update the bit and move index for next call
    return true;
}

//function is called when tagbit is identified as word type
//it will write by reference the 13 next bits into the wordbits from DecodeFile
//returns true if bits are read successfully (no eof)
bool decoder_::readWordBits(std::ifstream &file, std::bitset<13> &bits)
{
    for (int i = 13 - 1; i >= 0; i--) {//run until all 13 bits are entered
        bool bit;
        if (!readNextBit(file, bit)) return false;
        bits.set(i, bit);//append each bit
    }
    return true;
}

//function is called when tagbit is identified as character type
//it will write by reference the 6 next bits into the wordbits from DecodeFile
//returns true if bits are read successfully (no eof)
bool decoder_::readCharBits(std::ifstream &file, std::bitset<6> &bits)
{
    for (int i = 6 - 1; i >= 0; i--) {//run until all 6 bits are entered
        bool bit;
        if (!readNextBit(file, bit)) return false;
        bits.set(i, bit);//append each bit
    }
    return true;
}
