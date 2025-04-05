#ifndef PARSER_H
#define PARSER_H

#include <fstream>
#include <string>

/**
 * @brief Parser submodule
 *
 * @details
 * The `parser_` class provides helper methods that interact with user input.
 * Command line arguments will be converted into a format that is useful to the system.
 */
class parser_
{
    public:
        /**
         * @brief Returns true if the given filename represents a valid file
         * @param filename the filename to check
         * @return true if filename is a valid file
         */
        bool isValidFile(const std::string& filename);

        /**
         * @brief Creates a file that can be used by other submodules, doubles as output file and erl file
         * @param filename the filename to create
         */
        void createOutputFile(const std::string& filename);

        /**
         * @brief Converts command line inputs to useful format
         * @param argc number of command line args
         * @param argv command line args
         * @param messageFile return parameter for the message filename
         * @param dictionaryFile return parameter for the dictionary filename
         * @return true if successful
         */
        bool parseArguments(int argc, char* argv[], std::string& messageFile, std::string& dictionaryFile);

        /**
         * @brief Returns true if the given filename is an empty file
         * @param filename the filename to check
         * @return true if filename is empty
         */
        bool isFileEmpty(const std::string& filename);

    private:
        //can add members or functions if needed
};

#endif // PARSER_H