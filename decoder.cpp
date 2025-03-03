#include "decoder.h"

//function solely for checking file extension
bool hasExtension(const std::string& filename, const std::string& extension) {
    return filename.size() >= extension.size() &&
           filename.compare(filename.size() - extension.size(), extension.size(), extension) == 0;
}

//this function opens the declared target files, input = .erl and output = .txt
//then it 
bool decoder_::decodeFile(const std::string& inputFilename, const std::string& outputFilename)
{
    // Ensure the input file has a .erl extension
    if (!hasExtension(inputFilename, ".erl")) {
        std::cerr << "Error: Input file must have a .erl extension.\n";
        return false;
    }

    // Ensure the output file has a .txt extension
    if (!hasExtension(outputFilename, ".txt")) {
        std::cerr << "Error: Output file must have a .txt extension.\n";
        return false;
    }
    
    //make sure file opens
    std::ifstream inputFile(inputFilename, std::ios::binary);
    std::ofstream outputFile(outputFilename);
    if (!inputFile.is_open() || !outputFile.is_open()) {
        return false;
    }
    
    while (!inputFile.eof()) {
        bool tagBit;
        if (!readNextBit(inputFile, tagBit)) break; //pull the next bit,if at the end of the file break
        
        if (tagBit) { // Character mode - 1
            bit_code_6_ charBits;
            if (!readBits(inputFile, 6, charBits)) break;//will read the next 6bits into wordbits
            outputFile << wb.code_to_char(charBits);//find corresponding character and append to file
        } else { // Word mode - 0
            bit_code_13_ wordBits;//13 bit
            if (!readBits(inputFile, 13, wordBits)) break; //will read the next 13bits into wordbits
            outputFile << wb.code_to_word(wordBits) << " "; //find corresponding word and append to file
        }
    }
    
    inputFile.close(); //close files
    outputFile.close();
    return true; //if successful run through
}


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
bool decoder_::readBits(std::ifstream &file, int numBits, std::bitset<13> &bits)
{
    for (int i = numBits - 1; i >= 0; i--) {//run until all 6 bits are entered
        bool bit;
        if (!readNextBit(file, bit)) return false;
        bits.set(i, bit);//append each bit
    }
    return true;
}

//function is called when tagbit is identified as character type
//it will write by reference the 6 next bits into the wordbits from DecodeFile
//returns true if bits are read successfully (no eof)
bool decoder_::readBits(std::ifstream &file, int numBits, std::bitset<6> &bits)
{
    for (int i = numBits - 1; i >= 0; i--) {//run until all 6 bits are entered
        bool bit;
        if (!readNextBit(file, bit)) return false;
        bits.set(i, bit);//append each bit
    }
    return true;
}
