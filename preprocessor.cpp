#include "preprocessor.h"

// void preprocessor_::preprocessorTestbench(std::string inputFile)
// {
//     if ( !setUp(inputFile, "abcdefghijklmnopqurstuvwxyz,./;:\'\"1234567890!?-", "-!?,./;:\'\"") )
//         {
//             std::cout<<"Not found\n";
//             return;
//         }

//     std::vector<std::string> words;
//     std::string word;
//     while(iFile>>word)
//     {
//         words = convertWord(word);
//         std::cout<<word<<"\t\t";
//         for(int i=0;i<words.size();i++)
//         {   
//             std::cout << words.at(i) << " ";
//         }
//         std::cout<<std::endl;
//     }
// }

bool preprocessor_::setUp(std::string inputFile, std::string eChars, std::string puncChars)
{
    iFile.open(inputFile);
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
    return;
}

void preprocessor_::setPuncChars(std::string puncChars)
{
    puncuationChars = puncChars;
    return;
}

bool preprocessor_::fileStillGood()
{
    return iFile.good();
}

std::string preprocessor_::readWord()
{
    std::string word;
    iFile>>word;
    return word;
}

std::vector<std::string> preprocessor_::convertWord(std::string word)
{
    /// TODO: Swap this order to:
    // modifier -> lowercase -> removeNonexisting -> separate
    // Does removeNonexisting really need to operate on a vector<string> ?
    return removeNonexisting(separate(lowercase(modifier(word))));
}

std::string preprocessor_::modifier(std::string word)
{
    for(int iter=0;iter<word.size();iter++)
    {
        // debugging statement, will keep just in case
        // std::cout << std::hex << (0xFF & static_cast<int>(word[iter])) << ' ';

        unsigned char byte1 = (iter<word.size())?   word[iter] : 0;
        unsigned char byte2 = (iter+1<word.size())?   word[iter+1] : 0;
        unsigned char byte3 = (iter+2<word.size())?   word[iter+2] : 0;
        unsigned char byte4 = (iter+3<word.size())?   word[iter+3] : 0;

        /* 4-byte */
        if (byte1 >= 0xF0 && byte1 <= 0xF4) {
        if (byte2 >= 0x80 && byte2 <= 0xBF) {
        if (byte3 >= 0x80 && byte3 <= 0xBF) {
        if (byte4 >= 0x80 && byte4 <= 0xBF) {
            word[iter] = transliterateToASCII(word.substr(iter,4));
            word.erase(iter + 1, 3);
        }}}}

        /* 3-byte */
        if (byte1 >= 0xE0 && byte1 <= 0xEF) {
        if (byte2 >= 0x80 && byte2 <= 0xBF) {
        if (byte3 >= 0x80 && byte3 <= 0xBF) {
            word[iter] = transliterateToASCII(word.substr(iter,3));
            word.erase(iter + 1, 2);
        }}}

        /* 2-byte */
        if (byte1 >= 0xC2 && byte1 <= 0xDF) {
        if (byte2 >= 0x80 && byte2 <= 0xBF) {
            word[iter] = transliterateToASCII(word.substr(iter,2));
            word.erase(iter + 1, 1);
        }}

        /* 1-byte */                // do nothing
        // if (byte1 >= 0x00 && byte1 <= 0x7F) {
        // }

    } // end FOR
    return word;
}

// char preprocessor_::decomposer(std::string UTF_8_Bytes)
// {
//     std::cout<<UTF_8_Bytes<<"\n";
//     icu::UnicodeString utf8String = icu::UnicodeString::fromUTF8(UTF_8_Bytes);
//
//     UErrorCode status = U_ZERO_ERROR;
//     icu::UnicodeString decomposedString;
//     icu::Normalizer::decompose(utf8String, FALSE, 0, decomposedString, status);
//
//     if (U_SUCCESS(status)) {
//         std::string result;
//         decomposedString.toUTF8String(result);
//         std::cout << "Decomposed string: " ;
//         for(int i=0;i<result.size();i++)
//         {
//             std::cout << std::hex<< (0xFF & static_cast<int>(result[i])) << ' ';
//         }
//         std::cout<<"\n";
//         return result[0];
//     } else
//         std::cerr << "Error during decomposition: " << u_errorName(status) << std::endl;
//
//     return 0x00;
// }

/// TODO: Should this be reworked to remove the ICU dependency?
/// TODO: Get this to work on windows
char preprocessor_::transliterateToASCII(std::string input) {
    try {
        icu::UnicodeString str = icu::UnicodeString::fromUTF8(input);
        UErrorCode status = U_ZERO_ERROR;
        std::unique_ptr<icu::Transliterator> translit(
            icu::Transliterator::createInstance("NFKD; [:Nonspacing Mark:] Remove; Any-Latin; Latin-ASCII", UTRANS_FORWARD, status));

        if (U_FAILURE(status)) {
            std::cerr << "Failed to create ICU Transliterator\n";
            return 0x00;
        }

        translit->transliterate(str);
        std::string output;
        str.toUTF8String(output);
        return output[0]; // assuming output is not empty
    } catch (const std::exception& e) {
        std::cerr << "Exception occurred: " << e.what() << "\n";
        return 0x00;
    }
}

std::string preprocessor_::lowercase(std::string word)
{
    for(int i=0;i<word.size();i++)
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

    for(int i=0;i<word.size();i++)
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
            if(i!=(word.size()-1)) words.push_back("");
            numWord++;
        }

    }

    return words;
}

bool preprocessor_::isPunc(char letter)
{
    // return (letter == '.' || letter == ',' || letter == '?' || letter == '!' || 
    // letter == '-' || letter == '+' || letter == '=' || letter == '/' || 
    // letter == ':' || letter == ';' || letter == '(' || letter == ')' || 
    // letter == '\'' || letter == '\"' || letter == '~' || letter == '@' || 
    // letter == '#' || letter == '$' || letter == '%' || letter == '&' || letter == '*');
    return (puncuationChars.find(letter) != std::string::npos);
}

std::vector<std::string> preprocessor_::removeNonexisting(std::vector<std::string> inWords)
{
    std::vector<std::string> outWords;
    for(int i=0;i<inWords.size();i++)
    {
        outWords.push_back("");
        for(int j=0;j<inWords[i].size();j++)
        {
            /// TODO: Add isExistingChar() helper to match isPunc()? Rename?
            if(existingChars.find(inWords[i][j]) != std::string::npos)
            {
                outWords[i] += inWords[i][j];
            }
        }
    }
    return outWords;
}
