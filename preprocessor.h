#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

class preprocessor_
{
    public:

        // Multiple methods of setting up the preprocessor
        // Could be just setUp
        bool setUp(std::string fileString, std::string existingChars, std::string puncChars);
            // preprocessor initialization functions
            bool setFile(std::string fileString);
            void setExistingChars(std::string existingChars);
            void setPuncChars(std::string puncChars);

        std::string readLine();

        std::vector<std::string> convertWord(std::string word);

        bool fileGood();

    private:

        // Data members
        std::ifstream iFile;
        std::string existingChars;
        std::string puncuationChars;
        
        // preprocessor operating functions
        std::string lowercase(std::string word);
        std::vector<std::string> separate(std::string word);
        std::vector<std::string> removeNonexisting(std::vector<std::string> outWord);

        // helper functions
        bool isPunc(char letter);
        bool isChar(char letter);
};

#endif