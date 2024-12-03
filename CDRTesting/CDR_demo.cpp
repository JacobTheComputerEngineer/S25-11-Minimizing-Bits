#include <iostream>
#include <fstream>
#include <unordered_map>
#include <bitset>
#include <cstdint>
#include <sstream>
#include <map>
#include <vector>

// typedef std::map<std::string, std::string> WordBank;
typedef std::vector<std::pair<std::string, std::string>> WordBank;

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

        word_bank.push_back(std::make_pair(common_word, binary_code));
        code_point++;
    }

    return word_bank;
}


int main() {

    std::cout << "CDR Demo..." << std::endl;

    std::string filename;

    filename = "dict.txt";
    WordBank word_bank = construct_word_bank(filename);

    for (auto word_code_pair : word_bank) {
        std::string word = word_code_pair.first;
        std::string code = word_code_pair.second;

        std::cout << word << " : " << code << std::endl;
    }

}
