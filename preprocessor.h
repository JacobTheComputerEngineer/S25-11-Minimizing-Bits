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
        // void preprocessorTestbench(std::string inputFile);

        ///// TODO: Consolidate these to constructor?
        // preprocessor_();
        bool setUp(std::string inputFile, std::string existingChars, std::string puncChars);
        bool setFile(std::string file);
        void setExistingChars(std::string existingChars);
        void setPuncChars(std::string puncChars);
        /////

        ///// TODO: Is an input file really necessary for this?
        bool fileStillGood();
        std::string readWord();
        //////

        // This can stay as a public method
        std::vector<std::string> convertWord(std::string word);

        ///// TODO: Move to private methods?
        // How to test it then? -> test convertWord overall as that is the high level API
        std::string modifier(std::string word);
            char transliterateToASCII(std::string input); 
        std::string lowercase(std::string word);
        std::vector<std::string> separate(std::string word);
        bool isPunc(char letter);
        ///// TODO: Does removeNonexisting really need to operate on a vector<string> ?
        std::vector<std::string> removeNonexisting(std::vector<std::string> outWord);
        /////

    private:
        std::ifstream iFile;
        std::string existingChars;
        std::string puncuationChars;
        // std::string modifier(std::string word);
        //     char transliterateToASCII(std::string input); 
        // std::string lowercase(std::string word);
        // std::vector<std::string> separate(std::string word);
        //     bool isPunc(char letter);
        // std::vector<std::string> removeNonexisting(std::vector<std::string> outWord);
};