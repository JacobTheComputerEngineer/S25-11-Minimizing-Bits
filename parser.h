#ifndef PARSER_H
#define PARSER_H

#include <fstream>
#include <string>


class parser_
{
    public:
        bool isValidFile(const std::string& filename);

        //potentially more functions for reading the file
        void createOutputFile(const std::string& filename); //doubles as output file and erl file
        bool parseArguments(int argc, char* argv[], std::string& messageFile, std::string& dictionaryFile);
        bool parser_::isFileEmpty(const std::string& filename);

    private:
        //can add members or functions if needed
};

#endif // PARSER_H