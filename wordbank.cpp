#include "wordbank.h"

void wordbank_::construct(const std::string& filename) {
    build_word_map(filename);
    build_char_map();
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

// TODO: Adjust these as needed
std::string wordbank_::getExistingChars() {
    return "abcdefghijklmnopqrstuvwxyz0123456789.,?!-+=/:;()\'\"~@#$%&*";
}

// TODO: Adjust these as needed
std::string wordbank_::getPunctuationChars() {
    return ".,?!-+=/:;()\'\"~@#$%&*";
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

    /// TODO: Assert size == 8192
    // std::cout << "Final wb size = " << i << std::endl;
}

void wordbank_::build_char_map() {
    std::vector<std::string> char_list {
        "a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m",
        "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z",
        "0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
        ".", ",", "?", "!", "-", "+", "=", "/", ":", ";", "(", ")", "\'",
        "\"", "~", "@", "#", "$", "%", "&", "*", 
        "sh", "ch", "th", "ck", "ie", "ea", "ee"
    };

    for (std::size_t i = 0; i < char_list.size(); ++i) {
        forward_char_map[char_list[i]] = bit_code_6_(i);
        reverse_char_map[bit_code_6_(i)] = char_list[i];
    }

    // TODO: Assert size == 64
    // std::cout << "Final char wb size = " << forward_char_map.size() << std::endl;
}
