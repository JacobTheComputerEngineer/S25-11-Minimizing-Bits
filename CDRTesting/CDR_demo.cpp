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

bool contains(WordBank& bank, std::string key) {
    return bank.find(key) != bank.end();
}

int main() {

    std::cout << "CDR Demo..." << std::endl;

    std::string filename = "dict.txt";
    WordBank word_bank = construct_word_bank(filename);

    CharBank char_bank = construct_char_bank();

    std::ostringstream oss;

    

    std::string erl = oss.str();
    std::cout << "Binary: " << std::endl;
    std::cout << erl << std::endl;
}
