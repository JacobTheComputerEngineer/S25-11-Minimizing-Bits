#include "decoder.h"
#include "encoder.h"
#include "parser.h"
#include "preprocessor.h" // contains linux only header files
#include "wordbank.h"

#include <string>
#include <iostream>
#include <fstream>
// need to do the following to get the headers
// apt install libicu-dev
// apt install pkg-config

// use the following to compile
// g++ -o test_icu main.cpp preprocessor.cpp $(pkg-config --cflags --libs icu-uc icu-i18n)

//function solely for checking file extension
bool hasExtension(const std::string& filename, const std::string& extension) {
    return filename.size() >= extension.size() &&
           filename.compare(filename.size() - extension.size(), extension.size(), extension) == 0;
}

class ERL
{
    public:
        parser_ par;
        // TO DO : 



        preprocessor_ pre;
        // TO DO : 
        //  complete punctuation separation list
        //  add logic to character exists
        //  implement character exists


        encoder_ enc;
        // TO DO : 



        decoder_ decoder;
        // TO DO : 


        
        wordbank_ wb;
        // TO DO : 




        //functions connecting modules here
        //module specific functions in each module

        // suggested functions and connections
        //  void loadFiles (parser, wb, pre)
        //      input file from the given from the parser updates the file value of wb and pre
        //  void loadCharsets (wb, pre)
        //      upload the character bank (full and punctuation) to the preprocessor
        //  void encode  (pre, enc)
        //      a loop that receives a word from pre and gives it to enc
        //  bool checkCommon (enc, wb)
        //      enc gives a word to wb, wb returns if common

    private:

};

int main(int argc, char *argv[])
{
    ERL erl;

    std::cout << "Running ERL correctly..." << std::endl;



//decoder function, saving in main sothat decoder.cpp is complete
    decoder_ decoder;
    wordbank_ wb;
    std::string inputFilename = "DecoderBtest.erl";
    std::string outputFilename = "DecoderTtest.txt";
    if (!hasExtension(inputFilename, ".erl")) {
        std::cerr << "Error: Input file must have a .erl extension.\n";
        return 1;
    }

    if (!hasExtension(outputFilename, ".txt")) {
        std::cerr << "Error: Output file must have a .txt extension.\n";
        return 1;
    }

    std::ifstream inputFile(inputFilename, std::ios::binary);
    std::ofstream outputFile(outputFilename);
    if (!inputFile.is_open() || !outputFile.is_open()) {
        std::cerr << "Error: Unable to open input or output file.\n";
        return 1;
    }
    while (!inputFile.eof()) {
        bool tagBit;
        if (!decoder.readNextBit(inputFile, tagBit)) break;

        if (tagBit) { // Character mode - 1
            bit_code_6_ charBits;
            if (!decoder.readBits(inputFile, 6, charBits)) break;
            outputFile << wb.code_to_char(charBits);
        } else { // Word mode - 0
            bit_code_13_ wordBits;
            if (!decoder.readBits(inputFile, 13, wordBits)) break;
            outputFile << wb.code_to_word(wordBits) << " ";
        }
    }
    inputFile.close();
    outputFile.close();
    std::cout << "Decoding complete. Output saved to " << outputFilename << "\n";
//end decoder save




    return 0;
}