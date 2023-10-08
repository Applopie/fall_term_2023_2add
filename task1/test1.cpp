#define CATCH_CONFIG_MAIN

#include "catch.hpp"
#include "hw1longar.cpp"

TEST_CASE()
{
    LongNum a("544342");
    LongNum b("1235444");
    LongNum arev("-544342");
    LongNum x("13");
    LongNum c("1779786");
    LongNum d("-544355");
    LongNum e("7076446");

    REQUIRE(a + b == c);
    REQUIRE(a * x == e);
    REQUIRE(arev - x == d);
}