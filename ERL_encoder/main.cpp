#include "decoder.h"
#include "encoder.h"
#include "parser.h"
#include "preprocessor.h" // contains linux only header files
#include "wordBank.h"

// need to do the following to get the headers
// apt install libicu-dev
// apt install pkg-config

// use the following to compile
// g++ -o test_icu main.cpp preprocessor.cpp $(pkg-config --cflags --libs icu-uc icu-i18n)

class ERL
{
    public:
        parser_ par;
        // TO DO : 



        preprocessor_ pre;
        // TO DO : 
        //  complete punctuation separation list
        //  add logic to character exists
        //  implement character exists


        encoder_ enc;
        // TO DO : 



        decoder_ dec;
        // TO DO : 


        
        wordBank_ wb;
        // TO DO : 




        //functions connecting modules here
        //module specific functions in each module

        // suggested functions and connections
        //  void loadFiles (parser, wb, pre)
        //      input file from the given from the parser updates the file value of wb and pre
        //  void loadCharsets (wb, pre)
        //      upload the character bank (full and punctuation) to the preprocessor
        //  void encode  (pre, enc)
        //      a loop that receives a word from pre and gives it to enc
        //  bool checkCommon (enc, wb)
        //      enc gives a word to wb, wb returns if common

    private:

};

int main(int argc, char *argv[])
{
    ERL erl;

    // Testing the preprocessor
    erl.pre.preprocessorTestbench("preprocessorTestFile.txt");


    return 0;
}