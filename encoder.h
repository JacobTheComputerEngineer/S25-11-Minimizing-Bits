#ifndef ENCODER_H
#define ENCODER_H

#include <string>
#include <bitset>
#include <iostream>
#include <fstream>

typedef std::bitset<13> bit_code_13_;
typedef std::bitset<6> bit_code_6_;

/**
 * @brief Encoder submodule
 *
 * @details
 * The `encoder_` class provides several helper methods that interact with a given
 * .erl file. By utilizing these methods, we can safely write non-byte aligned codes
 * to the .erl.
 */
class encoder_
{

public:

	/**
     * @brief Function to print codes for common words, given as a 13-bit std::bitset
     * @param code the 13-bit word code to write to the file
     * @return true if successful
     */
	bool printWord(bit_code_13_ code);

	/**
     * @brief Function to print codes for individual characters, given as a 6-bit std::bitset
     * @param code the 6-bit word code to write to the file
     * @return true if successful
     */
	bool printCharacter(bit_code_6_ code);

	/**
     * @brief Function to append "full" buffer to binary output .erl file
     * @return true if successful
     */
	bool appendToFile();

	/**
     * @brief Sets and opens the output file for the encoder
     * @param filename the filename to use
     */
	void setOutputFile(std::string filename);

	/**
     * @brief Closes the output file
     */
	void closeOutputFile();

private:

	/**
     * @brief 8-bit bitset that will have its contents printed to output binary file when full
     */
	std::bitset<8> buffer;

	/**
     * @brief Marker of where to start filling buffer when new code is received so as not to overwrite leftover bits from past encoded word
     */
	std::size_t index = 7;

	/**
     * @brief Output file stream object
     */
	std::ofstream write;

};

#endif