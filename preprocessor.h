#ifndef PREPROCESSOR_H
#define PREPROCESSOR_H

#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iostream>

/**
 * @brief Preprocessor submodule
 *
 * @details
 * The `preprocessor_` class provides methods to convert words to the proper format for encoding.
 * The following conversions are made:
 * - All letters are converted to lowercase
 * - All punctuation marks are separated on both sides by spaces
 * - Any unrecognized characters are replaced by an unknown symbol (?)
 */
class preprocessor_
{
    public:

        // Multiple methods of setting up the preprocessor
        // Could be just setUp

        /**
         * @brief Sets up the preprocessor object
         * @param fileString the input filename
         * @param eChars the set of characters existing in the word bank
         * @param puncChars the set of punctuation marks existing in the word bank
         * @return true if successful
         */
        bool setUp(std::string fileString, std::string eChars, std::string puncChars);

        // preprocessor initialization functions

        /**
         * @brief Sets the input file for the preprocessor
         * @param fileString the input filename
         * @return true if successful
         */
        bool setFile(std::string fileString);

        /**
         * @brief Sets the existing character set for the preprocessor
         * @param eChars the set of existing characters
         * @return true if successful
         */
        void setExistingChars(std::string eChars);

        /**
         * @brief Sets the punctuation mark set for the preprocessor
         * @param existingChars the set of punctuation marks
         * @return true if successful
         */
        void setPuncChars(std::string puncChars);

        /**
         * @brief Reads a line from the input file
         * @return the line as a std::string
         */
        std::string readLine();

        /**
         * @brief Converts a given word following the definitions of the preprocessor
         * @param word the word to convert
         * @return a vector of strings to contain any substrings identified as words or punctuation marks
         */
        std::vector<std::string> convertWord(std::string word);

        /**
         * @brief Returns true if the input file is still good
         * @return true if file is good
         */
        bool fileGood();

    private:

        // Data members
        /**
         * @brief Input file stream object
         */
        std::ifstream iFile;

        /**
         * @brief Set of existing characters
         */
        std::string existingChars;

        /**
         * @brief Set of punctuation characters
         */
        std::string puncuationChars;
        
        // preprocessor operating functions
        /**
         * @brief Converts a given word to lowercase
         * @param word the word to convert
         * @return word in lowercase
         */
        std::string lowercase(std::string word);

        /**
         * @brief Separates embedded punctuation marks into a vector of strings
         * @param word the word to convert
         * @return a vector of strings that places punctuation marks in separate strings
         */
        std::vector<std::string> separate(std::string word);

        /**
         * @brief Replaces any unrecognized characters with an unknown symbol (?)
         * @param inWords the words to convert
         * @return the output vector with any unknown characters removed
         */
        std::vector<std::string> removeNonexisting(std::vector<std::string> inWords);

        // helper functions
        /**
         * @brief Returns true if the letter is a punctuation mark
         * @param letter the letter to check
         * @return true if letter is a punctuation mark
         */
        bool isPunc(char letter);

        /**
         * @brief Returns true if the letter is a valid character
         * @param letter the letter to check
         * @return true if letter is a valid character
         */
        bool isChar(char letter);
};

#endif