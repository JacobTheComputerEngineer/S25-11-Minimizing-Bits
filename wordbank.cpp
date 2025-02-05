#include "wordbank.h"

wordbank_::wordbank_(): wordbank_("dictionary.txt") {}

wordbank_::wordbank_(const std::string& filename) {
    build_word_map(filename);

    for (auto pair : forward_word_map) {
        std::cout << pair.first << ": " << pair.second << std::endl;
    }

    for (std::size_t i = 0; i < forward_word_map.size(); ++i) {
        bit_code_13_ code(i);
        std::cout << i << "/" << code << ": " << code_to_word(code) << std::endl;
    }
}

bit_code_13_ wordbank_::word_to_code(const std::string& word) const {
    return forward_word_map.at(word);
}

std::string wordbank_::code_to_word(bit_code_13_ code) const {
    return reverse_word_map.at(code);
}

bit_code_6_ wordbank_::char_to_code(const std::string& c) const {
    return bit_code_6_();
}

std::string wordbank_::code_to_char(bit_code_6_ code) const {
    return std::string();
}

bool wordbank_::contains_word(const std::string& word) const {
    return false;
}

std::string wordbank_::getExistingChars() {
    return std::string();
}

std::string wordbank_::getPunctuationChars() {
    return std::string();
}

void wordbank_::build_word_map(const std::string& filename) {
    // TODO: Replace this by reading in from the file
    std::vector<std::string> words;
    words.push_back("hello");
    words.push_back("world");
    words.push_back("this");
    words.push_back("is");
    words.push_back("a");
    words.push_back("test");
    words.push_back("for");
    words.push_back("word");
    words.push_back("bank");

    // TODO: Assert words.size() <= 8192

    for (std::size_t i = 0; i < words.size(); ++i) {
        forward_word_map[words[i]] = bit_code_13_(i);
        reverse_word_map[bit_code_13_(i)] = words[i];
    }
}

void wordbank_::build_char_map() {

}
