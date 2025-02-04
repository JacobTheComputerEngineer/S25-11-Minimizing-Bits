#include <fstream>
#include <string>
#include <vector>
#include <iostream>

// apt install libicu-dev
// apt install pkg-config
// g++ -o test_icu main.cpp preprocessor.cpp $(pkg-config --cflags --libs icu-uc icu-i18n)

#include <unicode/unistr.h>
// #include <unicode/normlzr.h> // used in decomposer, not needed without it
#include <unicode/translit.h>

class preprocessor_
{
    public:
        void preprocessorTestbench(std::string inputFile);
        bool setUp(std::string inputFile, std::string existingChars, std::string puncChars);
        std::vector<std::string> convertWord(std::string word);
    private:
        std::ifstream iFile;
        std::string existingChars;
        std::string puncuationChars;
        std::string modifier(std::string word);
            // char decomposer(std::string UTF_8_Bytes); // outdated byt transliterateToASCII
            char transliterateToASCII(std::string input); 
        std::string lowercase(std::string word);
        std::vector<std::string> separate(std::string word);
            bool isPunc(char letter);
        std::vector<std::string> removeNonexisting(std::vector<std::string> outWord);
};