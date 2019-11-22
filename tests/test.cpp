#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../src/SpellChecker/SpellChecker.h"

TEST_CASE( "SpellChecker.correction", "[SpellChecker]" ) {
    SpellChecker checker("src/utils/word_freq.txt");

    REQUIRE( checker.correction("expresion") == "expression" );
    REQUIRE( checker.correction("hellp") == "help" );
    REQUIRE( checker.correction("goodb") == "good" );
    REQUIRE( checker.correction("ratps") == "rate" );
    REQUIRE( checker.correction("numbar") == "number" );
    REQUIRE( checker.correction("spriag") == "spring" );
}

TEST_CASE( "SpellChecker throws if given a bad path" ) {

    bool thrown = false;
    std::string badPath = "bad/path/adasd/does/not/exist";
    try
    {
       SpellChecker checker(badPath);
       FAIL( "Expected contructor to throw" );
    }
    catch(const std::runtime_error & e)
    {
        REQUIRE(std::string(e.what()) == "The path does not exist: " + badPath);
        thrown = true;
    }
    REQUIRE(thrown);
}