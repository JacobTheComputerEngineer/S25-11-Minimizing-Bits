#include "parser.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

bool parser_::isValidFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Error: File " << filename << " could not be opened." << std::endl;
        return false;
    }
    // could check if file is empty or leave for preprocessor
    return true;
}

void parser_::createOutputFile(const std::string& filename)
{
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Error: File " << filename << " could not be created." << std::endl;
        return;
    }
    file.close();
    std::cout << "Output file " << filename << " created successfully." << std::endl;
    //could add more logic if needed
}

bool parser_::parseArguments(int argc, char* argv[], std::string& messageFile, std::string& dictionaryFile)
{
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <message_file> <dictionary_file> <output_file>" << std::endl;
        return false;
    }

    messageFile = argv[1];
    dictionaryFile = argv[2];

    if (!isValidFile(messageFile)) {
        std::cerr << "Error: Message file invalid" << std::endl;
        return false;
    }

    if (!isValidFile(dictionaryFile)) {
        std::cerr << "Error: Dictionary file invalid" << std::endl;
        return false;
    }

    if (isFileEmpty(messageFile)) {
        std::cerr << "Error: Message file is empty." << std::endl;
        return false;
    }

    if (isFileEmpty(dictionaryFile)) {
        std::cerr << "Error: Dictionary file is empty." << std::endl;
        return false;
    }

    return true;
}

bool parser_::isFileEmpty(const std::string& filename)
{
    std::ifstream file(filename, std::ios::ate);
    if (!file) {
        std::cerr << "Error: Could not open file '" << filename << "'." << std::endl;
        return false; 
    }

    return file.tellg() == 0; 
}
