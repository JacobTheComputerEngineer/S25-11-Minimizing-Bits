#include <iostream>
#include <fstream>
#include <unordered_set>

// Useful constants
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

// Simulate a mock file pre-processor
// Only keep letters and numbers
// Force to lowercase
std::string mock_preprocessor(const std::string& word) {
    std::string result;
    for (char c : word) {
        if (std::isalpha(c)) {
            result += std::tolower(c);  // Convert to lowercase if it's an alphabet
        } else if (std::isdigit(c)) {
            result += c;  // Keep numbers unchanged
        }
    }
    return result;
}

double compute_savings(int ERL_bits, int ASCII_bits) {
    return 1 - (double)ERL_bits / (double)ASCII_bits;
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

    // Compute number of bits for each encoding scheme
    int ASCII_bits = 0;
    int ERL_NULL_bits = 0;
    int ERL_TAG_bits = 0;

    // Track stats
    int total_num_words = 0;
    int total_num_chars = 0;
    double avg_word_length = 0.0;
    int num_hits = 0;
    int num_misses = 0;
    double hit_rate = 0.0;

    double avg_length_missed_word = 0.0;        ///////////////////////// New stat?
    int miss_char_count = 0;

    std::string word;
    while (file >> word) {
        // Simulate File Preprocessor
        word = mock_preprocessor(word);

        // Helpful quantities
        int num_chars = word.size() + 1;  // Account for space
        bool bank_hit = contains_word(word_bank, word);

        // Keep track of stats
        total_num_words++;
        total_num_chars += num_chars;
        if (bank_hit) {
            num_hits++;
        }
        else {
            num_misses++;
        }

        // ASCII
        ASCII_bits += num_chars * ASCII_bits_per_char;
        
        // ERL w/ NULL
        if (bank_hit) {
            ERL_NULL_bits += ERL_bits_per_word;
        }
        else {
            // TODO: How to deal with consecutive uncommon words?
            // 14 bit null
            ERL_NULL_bits += ERL_bits_per_word;

            // Add bits depending on num chars
            ERL_NULL_bits += num_chars * ERL_bits_per_char;

            // 6 bit null
            ERL_NULL_bits += ERL_bits_per_char;
        }

        // ERL w/ TAG
        if (bank_hit) {
            ERL_TAG_bits += FLAG_bit + ERL_bits_per_word;
        }
        else {
            // Add a flag bit in front of each char
            ERL_TAG_bits += num_chars * (FLAG_bit + ERL_bits_per_char);
        }

        if(!bank_hit) miss_char_count += num_chars; //////////////////////////////////////
    }

    // Compute stats
    avg_word_length = (double)total_num_chars / (double)total_num_words;
    hit_rate = (double)num_hits / (double)(num_hits + num_misses);
    avg_length_missed_word = double(miss_char_count) / (double)num_misses;  ////////////////////////////

    // Output to console
    std::cout << "File: " << filename << std::endl;
    std::cout << "Encoding\t\t# bits\t\t% saving over ASCII" << std::endl;
    std::cout << "ASCII\t\t\t" << ASCII_bits << "\t\t" << compute_savings(ASCII_bits, ASCII_bits) << std::endl;
    std::cout << "ERL w/ NULL\t\t" << ERL_NULL_bits << "\t\t" << compute_savings(ERL_NULL_bits, ASCII_bits) << std::endl;
    std::cout << "ERL w/ TAG\t\t" << ERL_TAG_bits << "\t\t" << compute_savings(ERL_TAG_bits, ASCII_bits) << std::endl;
    std::cout << std::endl;

    std::cout << "Stats:" << std::endl;
    std::cout << "Total Num Characters: " << total_num_chars << std::endl;
    std::cout << "Total Num Words: " << total_num_words << std::endl;
    std::cout << "Avg Word Length: " << avg_word_length << std::endl;
    std::cout << "Total Word Bank Hits: " << num_hits << std::endl;
    std::cout << "Total Word Bank Misses: " << num_misses << std::endl;
    std::cout << "Word Bank Hit Rate: " << hit_rate << std::endl;

    std::cout << "Average length of missed word: " << avg_length_missed_word << std::endl;

    return EXIT_SUCCESS;
}
