#include "catch.hpp"

#include "parser.h"

#include <fstream>

TEST_CASE("Test file validation and if empty", "[parser]") {
    parser_ par;

    // Example test case
    std::string testfile = "preprocessorTestFile.txt";
    //check if input is a valid file
    REQUIRE(par.isValidFile(testfile) == true);
    //check if input is empty
    REQUIRE(par.isFileEmpty(testfile) == false);

}

TEST_CASE("Test file creation", "[parser]") {
    parser_ par;
    std::string testfile = "testoutput.txt";
    //create a file
    par.createOutputFile(testfile);
    //check if the file exists
    std::ifstream infile(testfile);
    REQUIRE(infile.good() == true);
    infile.close();
}

TEST_CASE("Test argument parsing", "[parser]") {
    parser_ par;
    std::string messageFile = "preprocessorTestFile.txt";
    std::string dictionaryFile = "defaultdictionary.txt";
    std::string outputFile = "output.erl";
    //check if the arguments are parsed correctly
    char* validArgs[] = { (char*)"program", (char*)"preprocessorTestFile.txt", (char*)"defaultdictionary.txt", (char*)"output.erl" };
    REQUIRE(par.parseArguments(4, validArgs, messageFile, dictionaryFile) == true);
    REQUIRE(messageFile == "preprocessorTestFile.txt");
    REQUIRE(dictionaryFile == "defaultdictionary.txt");
}

