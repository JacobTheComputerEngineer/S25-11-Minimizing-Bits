#include <iostream>
#include <fstream>
#include <random>

#define BitNumber 13
#define ASCIINumber 6
#define TagBit 1

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
    int BitsTag[101] = {};
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
                BitsTag[i] += TagBit + ASCIINumber * (word.size()+1);
            } 
            else BitsTag[i] += BitNumber + TagBit;
        }

        BitsASCII += 8*word.size() + 8; // +8 accounts for the space that is not read in
        
        totalWords += 1;
        totalChars += word.size() + 1;
    }

    averageWordLength = (double)totalChars / (double)totalWords;

    // Output to console
    std::cout << std::endl << std::endl;
    std::cout << "Total number of bits - ASCII encoding scheme: \t" << BitsASCII << std::endl;

    std::cout<<"Total number of bits in\t\t\t\tNull\t\tTag\n";
    for(int i = 0; i < 101; i++) {
        std::cout << "Total number of bits  with a " << i << "% error rate:\t" << Bits[i] ;
        if(Bits[i]>9999999) std::cout << "\t" << BitsTag[i] << std::endl;
        else std::cout << "\t\t" << BitsTag[i] << std::endl;
    }
    std::cout << "Total number of bits - ASCII encoding scheme: \t" << BitsASCII << std::endl;
    std::cout << std::endl;

    std::cout << "Total number of words: " << totalWords << std::endl;
    std::cout << "Total number of chars: " << totalChars << std::endl;
    std::cout << "Average length of word: " << averageWordLength << std::endl;
    std::cout << std::endl;

    std::cout << "Compared to ASCII, NULL saved \t# \tand \t%\tTag saved\t#\t\t%" << std::endl;

    for(int i = 0; i < 100; i++) {
        if(i<96) std::cout << "\t" << i << "% error rate:\t\t" << BitsASCII - Bits[i] << "\t\t" << 100-100*(double)Bits[i]/(double)BitsASCII << "\t\t\t" << BitsASCII - BitsTag[i] << "\t\t" << 100-100*(double)BitsTag[i]/(double)BitsASCII << std::endl;
        else std::cout << "\t" << i << "% error rate:\t\t" << BitsASCII - Bits[i] << "\t\t" << 100-100*(double)Bits[i]/(double)BitsASCII << "\t\t" << BitsASCII - BitsTag[i] << "\t\t" << 100-100*(double)BitsTag[i]/(double)BitsASCII << std::endl;
    }
        std::cout<<"\t100% error rate:\t" << BitsASCII - Bits[100] << "\t\t" << 100 - 100 * (double)Bits[100] / (double)BitsASCII << "\t\t" << BitsASCII - BitsTag[100] << "\t\t" << 100-100*(double)BitsTag[100]/(double)BitsASCII << std::endl;
    
    // std::cout<<"\t"<<i<<"% error rate:\t\t"<<BitsASCII - Bits[i]<<"\t\t"<<100-100*(double)Bits[i]/(double)BitsASCII<<"\n";
    //                        std::cout<<"\t100% error rate:\t"<<BitsASCII - Bits[100]<<"\t\t"<<100-100*(double)Bits[100]/(double)BitsASCII<<"\n";

    std::cout << std::endl << std::endl;
    return 0;
}