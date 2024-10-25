#include <iostream>
#include <fstream>
#include <unordered_set>

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

    std::cout << "Word Bank Size: " << word_bank.size() << std::endl;

    std::cout << contains_word(word_bank, "hello") << std::endl;
    std::cout << contains_word(word_bank, "world") << std::endl;
    std::cout << contains_word(word_bank, "notcontained") << std::endl;

    // TODO: Iterate through message file and compute ASCII bits and ERL bits

    return EXIT_SUCCESS;
}
