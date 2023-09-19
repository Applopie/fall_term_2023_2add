#include <iostream>
#include "toy_catch.hpp"

TEST_CASE("Test first") {
  REQUIRE(1 == 1);
  std::cout << "checkpoint 1:1\n";
  REQUIRE(2 == 3);
  std::cout << "checkpoint 1:2\n";
  REQUIRE(4 == 4);
}

TEST_CASE("Test 2 second") {
  REQUIRE(1 == 1);
  std::cout << "checkpoint 2:1\n";
  REQUIRE(2 == 2);
  std::cout << "checkpoint 2:2\n";
  REQUIRE(4 == 4);
}

/*
int main() {
  Test1();
  Test2();
}
*/
