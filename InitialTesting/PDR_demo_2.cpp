#include <iostream>
#include <fstream>
#include <unordered_set>

#define ASCII_bits_per_char 8

#define ERL_bits_per_char 6
#define ERL_bits_per_word 13

#define FLAG_bit 1

// Construct a mock word bank from a file
// Mock word bank contains only keys
std::unordered_set<std::string> construct_word_bank(std::string filename) {
    std::unordered_set<std::string> word_bank;

    std::ifstream file(filename);
    if (!file.good()) {
        std::cout << "WARNING: Word Bank File " << filename << " not found." << std::endl;
        return word_bank;
    }

    std::string common_word;
    while (file >> common_word) {
        word_bank.insert(common_word);
    }

    return word_bank;
}

// Returns true if word_bank contains word
bool contains_word(std::unordered_set<std::string>& word_bank, std::string word) {
    return word_bank.find(word) != word_bank.end();
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cout << "Please input a text file to simulate" << std::endl;
        std::cout << "For example: .\\PDR_demo_2.exe mobydick.txt" << std::endl;
        return EXIT_FAILURE;
    }

    std::string filename = argv[1];
    std::ifstream file(filename);

    if(!file.good())
    {
        std::cout << "File " << filename << " not found."<< std::endl;
        return EXIT_FAILURE;
    }

    std::string dict_filename = "dict.txt";
    std::unordered_set<std::string> word_bank = construct_word_bank(dict_filename);

    if (word_bank.empty()) {
        std::cout << "The word bank is empty."<< std::endl;
        return EXIT_FAILURE;
    }

    // TODO: Consider small probability of typos? This would force a conversion to 6-bit ASCII
    // This can be done by moving the below to its own function that takes in an error rate, then varying the error rate

    // TODO: Iterate through message file and compute ASCII bits and ERL bits
    // TODO: Compare ERL with NULL separators and tagged words
    
    int ASCII_bits = 0;
    int ERL_NULL_bits = 0;
    int ERL_TAG_bits = 0;

    std::string word;
    while (file >> word) {
        // ASCII

        // ERL w/ NULL

        // ERL w/ TAG
    }

    return EXIT_SUCCESS;
}
