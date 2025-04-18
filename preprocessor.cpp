#include "preprocessor.h"

bool preprocessor_::setUp(std::string fileString, std::string eChars, std::string puncChars)
{
    iFile.open(fileString);
    existingChars = eChars;
    puncuationChars = puncChars;
    return iFile.good();
}

bool preprocessor_::setFile(std::string file)
{
    iFile.open(file);
    return iFile.good();
}

void preprocessor_::setExistingChars(std::string eChars)
{
    existingChars = eChars;
}

void preprocessor_::setPuncChars(std::string puncChars)
{
    puncuationChars = puncChars;
}

std::string preprocessor_::readLine()
{
    std::string word;
    std::getline(iFile, word);
    return word;
}

std::vector<std::string> preprocessor_::convertWord(std::string word)
{
    return removeNonexisting(separate(lowercase(word)));
}

bool preprocessor_::fileGood()
{
    return iFile.good() && !iFile.eof();
}

std::string preprocessor_::lowercase(std::string word)
{
    for(std::size_t i=0;i<word.size();i++)
    {
        word.at(i) = tolower(word.at(i));
    }
    return word;
}

std::vector<std::string> preprocessor_::separate(std::string word)      // TALK ABOUT NOT INCLUDING ' 
{
    std::vector<std::string> words;
    int numWord = 0;
    words.push_back("");

    for(std::size_t i=0;i<word.size();i++)
    {
        if(!isPunc(word[i]))
        {
            words[numWord] += word[i];
        }
        else
        {
            words.push_back("");
            numWord++;
            words[numWord] += word[i];
            if(i!=(word.size()-1)) {
                words.push_back("");
            }
            numWord++;
        }

    }

    return words;
}

bool preprocessor_::isPunc(char letter)
{
    return (puncuationChars.find(letter) != std::string::npos);
}

std::vector<std::string> preprocessor_::removeNonexisting(std::vector<std::string> inWords)
{
    int offset = 0;
    std::vector<std::string> outWords;
    for(std::size_t i=0;i<inWords.size();i++)
    {
        if(!inWords[i].empty())
        {
            outWords.push_back("");
        }
        else
        {
            offset++;
        }

        for(std::size_t j=0;j<inWords[i].size();j++)
        {
            if(isChar(inWords[i][j]))
            {
                outWords[i-offset] += inWords[i][j];
            }
            else
            {
                outWords[i-offset] += '?';
            }
        }
    }
    return outWords;
}

bool preprocessor_::isChar(char letter)
{
    return (existingChars.find(letter) != std::string::npos);
}