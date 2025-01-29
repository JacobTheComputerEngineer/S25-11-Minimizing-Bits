#include <fstream>
#include <string>
#include <vector>
#include <iostream>

// apt install libicu-dev
// apt install pkg-config
// g++ -o test_icu main.cpp preprocessor.cpp $(pkg-config --cflags --libs icu-uc icu-i18n)
#include <unicode/unistr.h>
#include <unicode/normlzr.h>
#include <unicode/translit.h>

class preprocessor_
{
    public:
        void preprocessorTestbench(std::string inputFile);
        bool setUp(std::string inputFile);
        std::vector<std::string> convertWord(std::string word);
    private:
        std::ifstream iFile;
        std::string modifier(std::string word);
            bool checkExists(char letter);
            char decomposer(std::string UTF_8_Bytes);
            char transliterateToASCII(std::string input); // Does not exist from apt install libicu-dev
        std::string lowercase(std::string word);
        std::vector<std::string> separate(std::string word);
};