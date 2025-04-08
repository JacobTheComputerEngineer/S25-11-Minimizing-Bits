#include "decoder.h"
#include "encoder.h"
#include "parser.h"
#include "preprocessor.h"
#include "wordbank.h"

#include <string>
#include <iostream>
#include <fstream>

/**
 * @brief Check if the filename has the given extension
 * @param filename the filename to check
 * @param extension the desired file extension
 * @return true filename has the desired extension
 */
bool hasExtension(const std::string& filename, const std::string& extension) {
    return filename.size() >= extension.size() &&
           filename.compare(filename.size() - extension.size(), extension.size(), extension) == 0;
}

/**
 * @brief Container class for all submodules.
 *
 * @details
 * The `ERL` class acts as a central container or manager for the key components
 * involved in the system, including the parser, preprocessor, encoder, decoder,
 * and word bank. This design promotes modularity and simplifies interaction
 * between the submodules.
 *
 * Each public member corresponds to a core module in the data processing pipeline:
 * - `parser_ par` handles input parsing.
 * - `preprocessor_ pre` performs data preprocessing tasks.
 * - `encoder_ enc` manages encoding logic.
 * - `decoder_ dec` is responsible for decoding operations.
 * - `wordbank_ wb` stores and retrieves word data.
 *
 * The class currently does not encapsulate behavior (i.e., no methods),
 * but it serves as a structural and logical grouping of submodules.
 *
 */
class ERL
{
    public:
        parser_ par;

        preprocessor_ pre;

        encoder_ enc;

        decoder_ dec;
        
        wordbank_ wb;

    private:

};

/**
 * @brief Returns the file size of a file in bytes
 * @param filename the filename to check
 * @return The size of the file in bytes
 */
std::streampos getFileSize(const std::string& fileName) {
    std::ifstream file(fileName, std::ios::binary | std::ios::ate);  // Open file in binary mode, and move the read pointer to the end
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file!" << std::endl;
        return -1;
    }
    return file.tellg();  // tellg() returns the current position of the read pointer, which is at the end of the file
}

/**
 * @brief Performs the encoder algorithm on a given input file
 *        Expected usage: ./erl <MESSAGE .txt> <DICTIONARY .txt> <OUTPUT .erl>
 */
int demoEncode(int argc, char *argv[])
{
    std::string outfileName;
    std::string messageFileName;
    std::string dictName;
    ERL erl;
    erl.par.parseArguments(argc, argv, messageFileName, dictName);
    outfileName = argv[3];
    erl.par.createOutputFile(outfileName);
    std::ifstream input(messageFileName);
    erl.wb.construct(dictName);
    erl.pre.setUp(messageFileName, erl.wb.getExistingChars(), erl.wb.getPunctuationChars());
    erl.enc.setOutputFile(outfileName);

    // Keep track of stats
    uint32_t num_hits = 0;
    uint32_t num_misses = 0;

    bit_code_13_ wordCode;
    bit_code_6_ charCode;
    while(erl.pre.fileGood())  // Keep reading lines until file is done
    {
        std::string line = erl.pre.readLine();
        std::istringstream line_stream(line);

        std::string raw_word;
        while (line_stream >> raw_word) {  // Keep reading words until line is done
            // Do everything below here for each word in the line
            std::vector<std::string> word;
            word.push_back(raw_word);
            if(word.at(0).empty()) {
                break;
            } 
            word = erl.pre.convertWord(word[0]);

            for(std::size_t i=0;i<word.size();i++)
            {
                if(erl.wb.contains_word(word.at(i)))
                {
                    num_hits++;
                    wordCode = erl.wb.word_to_code(word.at(i));
                    if(!erl.enc.printWord(wordCode)) {
                        std::cout<<"Failed at word : "<<word.at(i)<<"\n";
                    }
                }
                else
                {
                    num_misses++;
                    // std::cout << "Printing by char\n";
                    for(std::size_t j=0;j<word.at(i).size();j++)
                    {
                        if (erl.wb.contains_char(word.at(i).substr(j, 2)))      // Check for digraphs to assign a single 6-bit character code to 2 adjacent letters
                        {
                            charCode = erl.wb.char_to_code(word.at(i).substr(j, 2));    // Assign single character code for 2 characters
                            j++;                                                        // Additional increment to j
                            if (!erl.enc.printCharacter(charCode)) {
                                std::cout << "Failed at char : " << word.at(i).substr(j-1, 2) << "\n";  // Use enc to print character code
                            }
                        }
                        else
                        {
                            charCode = erl.wb.char_to_code(word.at(i).substr(j, 1));    // Standard 6-bit code assignment for a single character in input .txt
                            if (!erl.enc.printCharacter(charCode)) {
                                std::cout << "Failed at char : " << word.at(i).substr(j, 1) << "\n";    // Use enc to print character code
                            }
                        }
                    }
                    if(!erl.enc.printCharacter(erl.wb.char_to_code(" "))) {
                        std::cout<<"Failed adding *\n";
                    }
                }
            }
            // Do everything above for every word in the line
        }

        // Now, insert a newline
        erl.enc.printCharacter(erl.wb.char_to_code("\n"));
    }

    bit_code_13_ flush = 0;
    erl.enc.printWord(flush);

    erl.enc.closeOutputFile();

    // Compute final stats
    double hit_rate = (double)(num_hits) / (double)(num_hits + num_misses);
    uint32_t original_size = (uint32_t)getFileSize(messageFileName);
    uint32_t erl_size = (uint32_t)getFileSize(outfileName);
    double savings_percent = 1.0 - (double)(erl_size) / (double)(original_size);

    std::cout << "Size of original: " << getFileSize(messageFileName) << "\n";
    std::cout << "Size of erl: " << getFileSize(outfileName) << "\n";
    std::cout << "Size Reduction: " << savings_percent * 100.0 << "%\n";
    std::cout << "Hit Rate: " << hit_rate * 100.0 << "%\n";

    return 0;
}

/**
 * @brief Performs the decoder algorithm on a given input file
 *        Expected usage: ./erl <BINARY .erl> <DICTIONARY .txt> <OUTPUT .txt>
 */
int demoDecode(int argc, char *argv[])
{
    std::string outfileName;
    std::string messageFileName;
    std::string dictName;
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
            if (!input.eof()) // Resolved an issue where decoder was printing flush word to output .txt; must ignore final word code printed to erl
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

    input.close();
    output.close();
    
    std::cout<<"Size of erl: "<<getFileSize(messageFileName)<<"\n";
    std::cout<<"Size of decoded: "<<getFileSize(outfileName)<<"\n";

    return 0;
}

/**
 * @brief Entry point for the system. The file extension of the input file (.txt or .erl) will automatically
 *        run either the encoder or decoder respectively.
 *        Expected usage: ./erl <INPUT> <DICTIONARY> <OUTPUT>
 */
int main(int argc, char *argv[])
{
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <message_file> <dictionary_file> <output_file>" << std::endl;
        return 0;
    }

    std::string input(argv[1]);
    if (input.find(".txt") != std::string::npos) {
        demoEncode(argc, argv);
    } 
    else if (input.find(".erl") != std::string::npos) {
        demoDecode(argc, argv);
    } 
    else {
        std::cerr << "message_file must be of type .txt or .erl\n";
    }
    return 0;
}