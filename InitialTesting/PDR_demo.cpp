#include <iostream>
#include <fstream>
#include <random>

#define BitNumber 14
#define ASCIINumber 6

// This is a test

int main(int argc, char* argv[])
{
    if(argc != 2) // requires text file input
    {
        std::cout << "Please input a text file to simulate" << std::endl;
        std::cout << "For example: .\\PDR_demo.exe mobydick.txt" << std::endl;
        return 0;
    }

    std::string filename = argv[1];
    std::fstream file(filename);

    if(!file.good())
    {
        std::cout << "File not found." << std::endl;
        return 0;
    }

    std::string word;
    int Bits[101] = {};   // 0-100 inclusive
    std::random_device rand;

    int BitsASCII = 0;

    int totalWords = 0;
    int totalChars = 0;
    double averageWordLength = 0;

    while(file >> word)
    {
        for(int i = 0; i < 101; i++) 
        {
            Bits[i] += BitNumber;
            if(rand() % 101 < i) {
                Bits[i] += ASCIINumber * (word.size()+1);
            } 
        }

        BitsASCII += 8*word.size() + 8; // +8 accounts for the space that is not read in
        
        totalWords += 1;
        totalChars += word.size() + 1;
    }

    averageWordLength = (double)totalChars / (double)totalWords;

    // Output to console
    std::cout << std::endl << std::endl;
    std::cout << "Total number of bits used with the ASCII encoding scheme: " << BitsASCII << std::endl;

    for(int i = 0; i < 101; i++) {
        std::cout << "Total number of bits in our encoding with a " << i << "% error rate:\t" << Bits[i] << std::endl;
    }
    std::cout << std::endl;

    std::cout << "Total number of words: " << totalWords << std::endl;
    std::cout << "Total number of chars: " << totalChars << std::endl;
    std::cout << "Average length of word: " << averageWordLength << std::endl;
    std::cout << std::endl;

    std::cout << "Compared to ASCII, bits saved \t# \tand \t%:" << std::endl;

    for(int i = 0; i < 101; i++) {
        std::cout << "\t" << i << "% error rate:\t\t" << BitsASCII - Bits[i] << "\t\t" << 100-100*(double)Bits[i]/(double)BitsASCII << std::endl;
    }
    
    // std::cout<<"\t"<<i<<"% error rate:\t\t"<<BitsASCII - Bits[i]<<"\t\t"<<100-100*(double)Bits[i]/(double)BitsASCII<<"\n";
    //                        std::cout<<"\t100% error rate:\t"<<BitsASCII - Bits[100]<<"\t\t"<<100-100*(double)Bits[100]/(double)BitsASCII<<"\n";

    std::cout << std::endl << std::endl;
    return 0;
}