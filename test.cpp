#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "SpellChecker.h"

TEST_CASE( "SpellChecker.correction", "[SpellChecker]" ) {
    SpellChecker checker("word_freq.txt");

    REQUIRE( checker.correction("expresion") == "expression" );
    REQUIRE( checker.correction("hellp") == "help" );
    REQUIRE( checker.correction("goodb") == "good" );
    REQUIRE( checker.correction("ratps") == "rate" );
    REQUIRE( checker.correction("numbar") == "number" );
    REQUIRE( checker.correction("strig") == "spring" );
}