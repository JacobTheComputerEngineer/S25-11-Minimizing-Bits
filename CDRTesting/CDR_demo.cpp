#include <iostream>
#include <fstream>
#include <unordered_map>
#include <bitset>
#include <cstdint>
#include <sstream>
#include <vector>

typedef std::unordered_map<std::string, std::string> WordBank;
typedef WordBank CharBank;

// Construct word bank from dictionary file
// Key = common word
// Value = 13-bit binary as a string
WordBank construct_word_bank(std::string filename) {
    WordBank word_bank;

    std::ifstream file(filename);
    if (!file.good()) {
        throw std::invalid_argument("Could not read dictionary file");
    }

    std::string common_word = "";
    uint16_t code_point = 0;
    while (file >> common_word) {
        std::bitset<13> bitset(code_point);

        std::ostringstream oss;
        oss << bitset;
        std::string binary_code = oss.str();

        word_bank[common_word] = binary_code;
        code_point++;
    }

    return word_bank;
}

// Construct reduced ascii table
// This is constant and does not change
CharBank construct_char_bank() {
    CharBank char_bank;

    std::vector<std::string> char_list;

    // Add characters 'a' to 'z' to the vector
    for (char c = 'a'; c <= 'z'; ++c) {
        char_list.push_back(std::string(1, c));
    }

    // Add digits '0' to '9' to the vector
    for (char d = '0'; d <= '9'; ++d) {
        char_list.push_back(std::string(1, d));
    }

    // Add special characters to the vector
    std::string special_chars = ".,?!-+=/:;()'\"~@#$%&*";
    for (char sc : special_chars) {
        char_list.push_back(std::string(1, sc));
    }

    // Add digraphs to the vector
    std::vector<std::string> digraphs = {"sh", "ch", "th", "ck", "ie", "ea", "ee"};
    for (const auto& digraph : digraphs) {
        char_list.push_back(digraph);
    }


    uint16_t code_point = 0;
    for (auto x : char_list) {
        std::bitset<6> bitset(code_point);

        std::ostringstream oss;
        oss << bitset;
        std::string binary_code = oss.str();

        char_bank[x] = binary_code;
        code_point++;
    }

    return char_bank;
}

// Return if the word bank contains the given key
bool contains(WordBank& bank, std::string key) {
    return bank.find(key) != bank.end();
}

// Set all characters to lowercase
// Split punctuation
std::vector<std::string> simulate_file_preprocessor(std::string word) {
    std::vector<std::string> words;
    std::string current_word;

    // Iterate over each character in the word
    for (size_t i = 0; i < word.length(); ++i) {
        char c = word[i];

        // If the character is a punctuation mark, split it
        if (std::ispunct(c)) {
            if (!current_word.empty()) {
                words.push_back(current_word);
                current_word.clear();
            }
            words.push_back(std::string(1, c)); // Add punctuation as a separate word
        }
        else {
            // Convert character to lowercase and add to the current word
            current_word += std::tolower(c);
        }
    }

    // If there's a remaining word, add it
    if (!current_word.empty()) {
        words.push_back(current_word);
    }

    return words;
}

int main() {

    std::cout << "CDR Demo..." << std::endl;

    std::string filename;

    filename = "dict.txt";
    WordBank word_bank = construct_word_bank(filename);

    CharBank char_bank = construct_char_bank();

    std::ostringstream oss;

    filename = "message.txt";
    std::ifstream file(filename);
    if (!file.good()) {
        throw std::invalid_argument("Could not read message file");
    }

    // STATS
    int num_hits = 0;
    int num_misses = 0;
    int erl_bits = 0;
    int ascii_bits = 0;

    std::string word;
    while (file >> word) {

        // Simulate File Pre-Processor
        std::vector<std::string> words = simulate_file_preprocessor(word);

        for (std::string sequence : words) {
            std::cout << sequence << std::endl;

            if (contains(word_bank, sequence)) {
                std::cout << "0" << word_bank[sequence] << std::endl;
                oss << "0" << word_bank[sequence];
            }
            else {
                // TOOD: Check for digraphs
                for (char c : sequence) {
                    std::string s(1, c);
                    std::cout << "1" << char_bank[s] << std::endl;
                    oss << "1" << char_bank[s];
                }
            }
        }
    }

    // Output to Console
    // std::cout << "ASCII Bits: " << ascii_bits << std::endl;
    // std::cout << "Num Bits: " << num_bits << std::endl;
    // std::cout << "Num Misses: " << num_misses << std::endl;


    std::cout << std::endl << std::endl;
    std::cout << "----------------------" << std::endl;
    std::cout << "Binary: " << std::endl;
    std::string erl = oss.str();
    std::cout << erl << std::endl;
}
