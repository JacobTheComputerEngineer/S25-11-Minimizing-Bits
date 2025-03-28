#include <fstream>
#include <iostream>
#include <unordered_set>
#include <string>

int main(int argc, char *argv[])
{
    if(argc!=2) std::cout<<"./ERlMakeDict <inputFileName>\n";
    std::string inString(argv[1]);
    std::ifstream inFile(inString);
    std::unordered_set<std::string> words;
    std::string outName = inString.substr(0,inString.rfind('.')) + "_dict.txt";
    std::ofstream outFile(outName);

    std::string word;
    while( inFile >> word)
    {
        if(words.find(word) == words.end() && words.size()<8192)
        {
            words.insert(word);
            outFile << word << "\n";
        }
    }
    return 0;
}