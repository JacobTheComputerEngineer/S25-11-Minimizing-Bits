#include <iostream>

#define MINWORDSIZE 1
#define MAXWORDSIZE 20

#define REDUCEDASCIISIZE 6
#define ERLBITSIZE 13
#define TAGBIT 1

#define ERLNULL 13
#define ASCIINULL 6

int main()
{
    int BitsTag = 0;
    int BitsNull = 0;
    
    for( int i = MINWORDSIZE ; i < MAXWORDSIZE ; i++ )
    {
        BitsTag =  i * ( TAGBIT + REDUCEDASCIISIZE );
        BitsNull = ERLNULL + ( i * REDUCEDASCIISIZE + ASCIINULL );

        std::cout << "Word length: " << i << std::endl;
        std::cout << "Tag bits needed: " << BitsTag << std::endl;
        std::cout << "Null bits needed: " << BitsNull << std::endl;
        std::cout << "Words in dict until even: " << abs(BitsNull-BitsTag) << std::endl;
        std::cout << "% of hits for even: " << 1 - 1.0 / ( (double)abs(BitsNull-BitsTag) + 1 ) << std::endl;
        std::cout << std::endl;
    }
}