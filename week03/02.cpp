// REQUIRE
// TEST_CASE

#define REQUIRE(value)             \
    do                             \
    {                              \
        bool v = Require((value)); \
        if (!v)                    \
            return;                \
    }

bool Require(bool value)
{
    if (!value)
    {
        std::cerr << "Test failed\n"
    }
    return value;
}

#include <iostream>

void Test1()
{
    REQUIRE(1 == 1);
    std::cout << "checkpoint 1:2\n";
    REQUIRE(1 == 1);
    std::cout << "checkpoint 1:2\n";
    REQUIRE(1 == 1);
}
