#ifndef ENCODER_H
#define ENCODER_H

#include <string>
#include <bitset>
#include <iostream>
#include <fstream>

typedef std::bitset<13> bit_code_13_;
typedef std::bitset<6> bit_code_6_;

// SOME ADDITIONAL IMPLEMENTATION TO BE COMPLETED IN MAIN, MAINLY CHECKING WITH WORD BANK TO OBTAIN BITCODES

class encoder_
{

public:

	/// TODO: Remove filename param from these three functions??
	bool printWord(bit_code_13_ code, std::string filename);		// Function to print codes for common words, given as a 13-bit std::bitset
	bool printCharacter(bit_code_6_ code, std::string filename);	// Function to print codes for individual characters, given as a 6-bit std::bitset
	bool appendToFile(std::string filename);						// Function to append "full" buffer to binary output .erl file

	void setOutputFile(std::string filename);
	void closeOutputFile();

private:

	std::bitset<8> buffer;	// 8-bit bitset that will have its contents printed to output binary file when full
	std::size_t index = 7;	// Marker of where to start filling buffer when new code is received so as not to overwrite leftover bits from past encoded word

	std::ofstream write;

};

#endif