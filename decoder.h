#ifndef DECODER_H
#define DECODER_H

#include <string>
#include <bitset>
#include <iostream>
#include <fstream>

typedef std::bitset<13> bit_code_13_;
typedef std::bitset<6> bit_code_6_;

/**
 * @brief Decoder submodule
 *
 * @details
 * The `decoder_` class provides several helper methods that interact with a given
 * .erl binary file. By utilizing these methods, we can safely read non-byte aligned codes
 * from the .erl.
 */
class decoder_
{
public:

    /**
     * @brief Reads the next bit, and by reference updates the bit in decodeFile
     * @param file the file stream to read from
     * @param bit output parameter for the bit that was read
     * @return true if bit is read successfully 
     */
    bool readNextBit(std::ifstream &file, bool &bit);

    /**
     * @brief Called when tag bit is identified as word type, 
     *        it will write by reference the 13 next bits into the wordbits from decodeFile
     * @param file the file stream to read from
     * @param bits output parameter for the bits that were read
     * @return true if bits are read successfully (no eof)
     */
    bool readWordBits(std::ifstream &file, std::bitset<13> &bits);

    /**
     * @brief Called when tag bit is identified as character type, 
     *        it will write by reference the 6 next bits into the wordbits from decodeFile
     * @param file the file stream to read from
     * @param bits output parameter for the bits that were read
     * @return true if bits are read successfully (no eof)
     */
    bool readCharBits(std::ifstream &file, std::bitset<6> &bits);
};
#endif // DECODER_H
