#include "catch.hpp"

#include "preprocessor.h"

TEST_CASE("setting up preprocessor", "[preprocessor]")
{
    preprocessor_ pre;

    REQUIRE(pre.setUp("preprocessorTestFile.txt", "abcdefghijklmnopqurstuvwxyz,./;:\'\"1234567890!?-", "-!?,./;:\'\""));

}

TEST_CASE("separation with punctuation", "[preprocessor]")
{
    preprocessor_ pre;
    pre.setExistingChars("qwertyuiopasdfghjklzxcvbnm,./?;:\'\"\\()!$%");
    pre.setPuncChars(",./?;:\'\"\\()!$%");

    std::vector<std::string> ansA;
    ansA.push_back("apple");
    REQUIRE(pre.convertWord("APPLE") == ansA);
    ansA.push_back("!");
    REQUIRE(pre.convertWord("apple!") == ansA);
    ansA.push_back("!");
    REQUIRE(pre.convertWord("apple!!") == ansA);

    std::vector<std::string> ansB;
    ansB.push_back("\"");
    ansB.push_back("hi");
    ansB.push_back("\"");
    REQUIRE(pre.convertWord("\"hi\"") == ansB);

    std::vector<std::string> ansC;
    ansC.push_back("separate");
    ansC.push_back("\'");
    ansC.push_back("apostrophes");
    REQUIRE(pre.convertWord("separate\'apostrophes") == ansC);

    pre.setPuncChars(",./?;:\"\\()!$%");
    std::vector<std::string> ansD;
    ansD.push_back("together\'apostrophes");
    REQUIRE(pre.convertWord("together\'apostrophes") == ansD);

    std::vector<std::string> ansE;
    ansE.push_back("unexpected?character");
    REQUIRE(pre.convertWord("unexpected*character") == ansE);
}