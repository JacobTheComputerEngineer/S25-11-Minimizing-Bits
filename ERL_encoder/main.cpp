#include "decoder.h"
#include "encoder.h"
#include "parser.h"
#include "preprocessor.h"
#include "wordBank.h"

class ERL
{
    public:
        parser_ par;
        preprocessor_ pre;
        encoder_ enc;
        decoder_ dec;
        wordBank_ wb;

        //functions connecting modules here
        //module specific functions in each module
    private:

};

int main(int argc, char *argv[])
{

}