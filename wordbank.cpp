#include "wordbank.h"

void wordbank_::construct(const std::string& filename) {
    build_word_map(filename);
    // build_char_map();
}

bit_code_13_ wordbank_::word_to_code(const std::string& word) const {
    return forward_word_map.at(word);
}

std::string wordbank_::code_to_word(bit_code_13_ code) const {
    return reverse_word_map.at(code);
}

bit_code_6_ wordbank_::char_to_code(const std::string& c) const {
    return forward_char_map.at(c);
}

std::string wordbank_::code_to_char(bit_code_6_ code) const {
    return reverse_char_map.at(code);
}

bool wordbank_::contains_word(const std::string& word) const {
    return forward_word_map.find(word) != forward_word_map.end();
}

std::string wordbank_::getExistingChars() {
    // TODO
    return std::string();
}

std::string wordbank_::getPunctuationChars() {
    // TODO
    return std::string();
}

void wordbank_::build_word_map(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.good()) {
        std::cout << "Could not find " << filename << std::endl;
        return;
    }

    std::size_t i = 0;
    std::string common_word;
    while (file >> common_word) {
        forward_word_map[common_word] = bit_code_13_(i);
        reverse_word_map[bit_code_13_(i)] = common_word;
        i++;
    }

    // TODO: Assert size == 8192
    std::cout << "Final wb size = " << i << std::endl;
}

void wordbank_::build_char_map() {
    // TODO
}
