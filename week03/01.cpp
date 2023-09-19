// тестировки Фреймворки: GTest Catch2(github) Boost.Test

#include <iostream>

#define CATCH_CONFIG_MAIN

#include "catch.hpp"

TEST_CASE("My_first_test")
{
    REQUIRE(1 == 1);
    REQUIRE(2 == 2);
    for (size_t i = 10; i < 100; ++i)
    {
        REQUIRE(i == i);
    }
}