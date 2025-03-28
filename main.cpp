#include "decoder.h"
#include "encoder.h"
#include "parser.h"
#include "preprocessor.h" // contains linux only header files
#include "wordbank.h"

#include <string>
#include <iostream>
#include <fstream>

// TODO
// Digraphs
// maybe newlines

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



        decoder_ dec;
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

// bbedit
// print out file size

std::streampos getFileSize(const std::string& fileName) {
    std::ifstream file(fileName, std::ios::binary | std::ios::ate);  // Open file in binary mode, and move the read pointer to the end
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file!" << std::endl;
        return -1;
    }
    return file.tellg();  // tellg() returns the current position of the read pointer, which is at the end of the file
}

int demoEncode(int argc, char *argv[])
{
    std::string outfileName, messageFileName, dictName;
    ERL erl;
    erl.par.parseArguments(argc, argv, messageFileName, dictName);
    outfileName = argv[3];
    erl.par.createOutputFile(outfileName);
    std::ifstream input(messageFileName);
    erl.wb.construct(dictName);
    erl.pre.setUp(messageFileName, erl.wb.getExistingChars(), erl.wb.getPunctuationChars());
    erl.enc.setOutputFile(outfileName);

    bit_code_13_ wordCode;
    bit_code_6_ charCode;
    while(erl.pre.fileGood())
    {
        std::vector<std::string> word;
        word.push_back(erl.pre.readWord());
        if(word.at(0).size() == 0) break;
        word = erl.pre.convertWord(word[0]);

        for(int i=0;i<word.size();i++)
        {
            if(erl.wb.contains_word(word.at(i)))
            {
                wordCode = erl.wb.word_to_code(word.at(i));
                if( ! erl.enc.printWord(wordCode,outfileName) ) std::cout<<"Failed at word : "<<word.at(i)<<"\n";
            }
            else
            {
                // std::cout << "Printing by char\n";
                for(int j=0;j<word.at(i).size();j++)
                {
                    if (erl.wb.contains_char(word.at(i).substr(j, 2)))      // Check for digraphs to assign a single 6-bit character code to 2 adjacent letters
                    {
                        charCode = erl.wb.char_to_code(word.at(i).substr(j, 2));    // Assign single character code for 2 characters
                        j++;                                                        // Additional increment to j
                        if (!erl.enc.printCharacter(charCode, outfileName)) std::cout << "Failed at char : " << word.at(i).substr(j-1, 2) << "\n";  // Use enc to print character code
                    }
                    else
                    {
                        charCode = erl.wb.char_to_code(word.at(i).substr(j, 1));    // Standard 6-bit code assignment for a single character in input .txt
                        if (!erl.enc.printCharacter(charCode, outfileName)) std::cout << "Failed at char : " << word.at(i).substr(j, 1) << "\n";    // Use enc to print character code
                    }
                }
                if(!erl.enc.printCharacter(erl.wb.char_to_code(" "),outfileName)) std::cout<<"Failed adding *\n";
            }
        }
    }

    bit_code_13_ flush = 0;
    erl.enc.printWord(flush, outfileName);

    erl.enc.closeOutputFile();

    std::cout<<"Size of original: "<<getFileSize(messageFileName)<<"\n";
    std::cout<<"Size of erl: "<<getFileSize(outfileName)<<"\n";

    return 0;
}

int demoDecode(int argc, char *argv[])
{
    std::string outfileName, messageFileName, dictName;
    ERL erl;
    erl.par.parseArguments(argc, argv, messageFileName, dictName);
    outfileName = argv[3];
    erl.par.createOutputFile(outfileName);
    std::ifstream input(messageFileName, std::ios::binary);
    std::ofstream output(outfileName);
    erl.wb.construct(dictName);

    bool bit;
    bit_code_13_ wordCode;
    bit_code_6_ charCode;
    std::string word;
    while(erl.dec.readNextBit(input, bit))
    {
        if(bit)
        {
            erl.dec.readCharBits(input, charCode);
            word = erl.wb.code_to_char(charCode);
            if (!input.eof())                       // MV 3/25/25 - Resolved an issue where decoder was printing flush word to output .txt; must ignore final word code printed to erl
            {
                output << word;
            }
        }
        else
        {
            erl.dec.readWordBits(input, wordCode);
            word = erl.wb.code_to_word(wordCode);
            if (!input.eof())
            {
                output << word << " ";
            }
        }
    }
    
    std::cout<<"Size of erl: "<<getFileSize(messageFileName)<<"\n";
    std::cout<<"Size of decoded: "<<getFileSize(outfileName)<<"\n";

    return 0;
}

int main(int argc, char *argv[])
{
//     ERL erl;

//     std::cout << "Running ERL correctly..." << std::endl;



// //decoder function, saving in main sothat decoder.cpp is complete
//     decoder_ decoder;
//     wordbank_ wb;
//     std::string inputFilename = "DecoderBtest.erl";
//     std::string outputFilename = "DecoderTtest.txt";
//     if (!hasExtension(inputFilename, ".erl")) {
//         std::cerr << "Error: Input file must have a .erl extension.\n";
//         return 1;
//     }

//     if (!hasExtension(outputFilename, ".txt")) {
//         std::cerr << "Error: Output file must have a .txt extension.\n";
//         return 1;
//     }

//     std::ifstream inputFile(inputFilename, std::ios::binary);
//     std::ofstream outputFile(outputFilename);
//     if (!inputFile.is_open() || !outputFile.is_open()) {
//         std::cerr << "Error: Unable to open input or output file.\n";
//         return 1;
//     }
//     while (!inputFile.eof()) {
//         bool tagBit;
//         if (!decoder.readNextBit(inputFile, tagBit)) break;

//         if (tagBit) { // Character mode - 1
//             bit_code_6_ charBits;
//             if (!decoder.readCharBits(inputFile, 6, charBits)) break;
//             outputFile << wb.code_to_char(charBits);
//         } else { // Word mode - 0
//             bit_code_13_ wordBits;
//             if (!decoder.readWordBits(inputFile, 13, wordBits)) break;
//             outputFile << wb.code_to_word(wordBits) << " ";
//         }
//     }
//     inputFile.close();
//     outputFile.close();
//     std::cout << "Decoding complete. Output saved to " << outputFilename << "\n";
//end decoder save

    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <message_file> <dictionary_file> <output_file>" << std::endl;
        return 0;
    }

    std::string input(argv[1]);
         if (input.find(".txt") != std::string::npos ) demoEncode(argc, argv);
    else if (input.find(".erl") != std::string::npos ) demoDecode(argc, argv);
    else std::cerr << "message_file must be of type .txt or .erl\n";
    return 0;
}