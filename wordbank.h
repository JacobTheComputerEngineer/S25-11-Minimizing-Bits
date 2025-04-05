#ifndef WORDBANK_H
#define WORDBANK_H

#include <string>
#include <unordered_map>
#include <bitset>
#include <iostream>
#include <fstream>
#include <vector>

typedef std::bitset<13> bit_code_13_;
typedef std::bitset<6> bit_code_6_;

/**
 * @brief Word Bank submodule
 *
 * @details
 * The `wordbank_` class provides methods to convert English to binary codes.
 * This is done using several hash maps to ensure amortized constant time lookups regardless of direction.
 * The word bank contents are populated on construction based on the dictionary file of 8192 words.
 */
class wordbank_
{
    public:

        /**
         * @brief Construct the word bank from a given dictionary file
         * @param filename the dictionary filename
         */
        void construct(const std::string& filename);

        // Access word bank
        /**
         * @brief Convert a word to a 13-bit binary code
         * @param word the word to convert
         * @return the 13-bit code corresponding to the word
         */
        bit_code_13_ word_to_code(const std::string& word) const;

        /**
         * @brief Convert a 13-bit binary code to a word
         * @param code the code to convert
         * @return the word corresponding to the 13-bit code
         */
        std::string code_to_word(bit_code_13_ code) const;

        // Access char bank
        /**
         * @brief Convert a character to a 6-bit binary code
         * @param c the character to convert
         * @return the 6-bit code corresponding to the character
         */
        bit_code_6_ char_to_code(const std::string& c) const;

        /**
         * @brief Convert a 6-bit binary code to a character
         * @param code the code to convert
         * @return the character corresponding to the 6-bit code
         */
        std::string code_to_char(bit_code_6_ code) const;

        // Helper functions
        /**
         * @brief Returns true if the word is contained in the word bank
         * @param word the word to check
         * @return true if word is in the word bank
         */
        bool contains_word(const std::string& word) const;

        /**
         * @brief Returns true if the character is contained in the character bank, used for digraph checking
         * @param c the character to check
         * @return true if c is in the character bank
         */
        bool contains_char(const std::string& c) const;

        /**
         * @brief Returns the set of existing characters in the character bank for the preprocessor
         * @return the set of existing characters
         */
        static std::string getExistingChars();

        /**
         * @brief Returns the set of punctuation characters in the character bank for the preprocessor
         * @return the set of punctuation characters
         */
        static std::string getPunctuationChars();

    private:

        /**
         * @brief The hash map for converting a word to a 13-bit code
         */
        std::unordered_map<std::string, bit_code_13_> forward_word_map;

        /**
         * @brief The hash map for converting a 13-bit code to a word
         */
        std::unordered_map<bit_code_13_, std::string> reverse_word_map;

        /**
         * @brief The hash map for converting a character to a 6-bit code
         */
        std::unordered_map<std::string, bit_code_6_> forward_char_map;

        /**
         * @brief The hash map for converting a 6-bit code to a character
         */
        std::unordered_map<bit_code_6_, std::string> reverse_char_map;

        /**
         * @brief Helper method to build the forward and reverse word hash maps
         * @param filename the dictionary file name
         */
        void build_word_map(const std::string& filename);

        /**
         * @brief Helper method to build the forward and reverse character hash maps
         */
        void build_char_map();

};

#endif