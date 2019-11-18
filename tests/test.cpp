#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "../src/SpellChecker/SpellChecker.h"

TEST_CASE( "SpellChecker.correction", "[SpellChecker]" ) {
    SpellChecker checker("utils/word_freq.txt");

    REQUIRE( checker.correction("expresion") == "expression" );
    REQUIRE( checker.correction("hellp") == "help" );
    REQUIRE( checker.correction("goodb") == "good" );
    REQUIRE( checker.correction("ratps") == "rate" );
    REQUIRE( checker.correction("numbar") == "number" );
    REQUIRE( checker.correction("spriag") == "spring" );

    // constructor should throw if no path or wrong path
    
}