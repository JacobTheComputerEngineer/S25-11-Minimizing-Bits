#include "wordbank.h"

wordbank_::wordbank_(): wordbank_("dictionary.txt") {}

wordbank_::wordbank_(const std::string& filename) {

}

bit_code_13_ wordbank_::word_to_code(const std::string& word) const {
    return bit_code_13_(0);
}

std::string wordbank_::code_to_word(bit_code_13_ code) const {
    return std::string();
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

}

void wordbank_::build_char_map() {

}
