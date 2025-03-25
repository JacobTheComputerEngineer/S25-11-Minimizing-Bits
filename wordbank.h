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

class wordbank_
{
    public:

        // Construct the word bank from a given dictionary file
        void construct(const std::string& filename);

        // Access word bank
        bit_code_13_ word_to_code(const std::string& word) const;
        std::string code_to_word(bit_code_13_ code) const;

        // Access char bank
        bit_code_6_ char_to_code(const std::string& c) const;
        std::string code_to_char(bit_code_6_ code) const;

        // Helper functions
        bool contains_word(const std::string& word) const;
        bool contains_char(const std::string& c) const;     // MV 3/25/25 - Used for digraph checking
        static std::string getExistingChars();
        static std::string getPunctuationChars();

    private:

        std::unordered_map<std::string, bit_code_13_> forward_word_map;
        std::unordered_map<bit_code_13_, std::string> reverse_word_map;

        std::unordered_map<std::string, bit_code_6_> forward_char_map;
        std::unordered_map<bit_code_6_, std::string> reverse_char_map;

        void build_word_map(const std::string& filename);
        void build_char_map();

};

#endif