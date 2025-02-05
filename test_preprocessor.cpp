#include "catch.hpp"

#include "preprocessor.h"

/// TODO: Test convertWord()
/// TODO: Test $ and @ don't get converted to S and a

TEST_CASE("example preprocessor test", "[preprocessor]") {
    preprocessor_ pre;

    // pre.preprocessorTestbench("preprocessorTestFile.txt");

    REQUIRE(true);
}

TEST_CASE("setting up preprocessor", "[preprocessor]")
{
    preprocessor_ pre;

    REQUIRE(pre.setUp("preprocessorTestFile.txt", "abcdefghijklmnopqurstuvwxyz,./;:\'\"1234567890!?-", "-!?,./;:\'\""));

}

TEST_CASE("converting expected words", "[preprocessor]")
{
    preprocessor_ pre;
    pre.setExistingChars("qwertyuiopasdfghjklzxcvbnm");

    std::string ans = "apple";
    std::vector<std::string> ansV;
    ansV.push_back("apple");
    REQUIRE(pre.modifier("apple") == ans);
    REQUIRE(pre.lowercase(pre.modifier("apple")) == ans);
    REQUIRE(pre.separate(pre.lowercase(pre.modifier("apple"))) == ansV);
    REQUIRE(pre.removeNonexisting(pre.separate(pre.lowercase(pre.modifier("apple")))) == ansV);
    
    REQUIRE(pre.removeNonexisting(pre.separate(pre.lowercase(pre.modifier("Apple")))) == ansV);
    REQUIRE(pre.removeNonexisting(pre.separate(pre.lowercase(pre.modifier("ApplE")))) == ansV);
    REQUIRE(pre.removeNonexisting(pre.separate(pre.lowercase(pre.modifier("APPLE")))) == ansV);
}

TEST_CASE("converting unexpected words", "[preprocessor]")
{
    preprocessor_ pre;
    pre.setExistingChars("qwertyuiopasdfghjklzxcvbnm");
    std::vector<std::string> ansV;
    ansV.push_back("apple");
    REQUIRE(pre.removeNonexisting(pre.separate(pre.lowercase(pre.modifier("àṕṕĺḗ")))) == ansV);
    REQUIRE(pre.removeNonexisting(pre.separate(pre.lowercase(pre.modifier("ĀṔṖĽĖ")))) == ansV);
    REQUIRE(pre.removeNonexisting(pre.separate(pre.lowercase(pre.modifier("ĀṔṖĽĖ")))) == ansV);
    REQUIRE(pre.removeNonexisting(pre.separate(pre.lowercase(pre.modifier("Ⱥƥƥŀɇ")))) == ansV);
    REQUIRE(pre.removeNonexisting(pre.separate(pre.lowercase(pre.modifier("ȺⱣⱣĿɆ")))) == ansV);
}

TEST_CASE("separation with punctuation", "[preprocessor]")
{
    preprocessor_ pre;
    pre.setExistingChars("qwertyuiopasdfghjklzxcvbnm,./?;:\'\"\\()!$%");
    pre.setPuncChars(",./?;:\'\"\\()!$%");
    std::vector<std::string> ansV;
    ansV.push_back("apple");
    ansV.push_back("!");

    REQUIRE(pre.removeNonexisting(pre.separate(pre.lowercase(pre.modifier("ȺⱣⱣĿɆ!")))) == ansV);
}