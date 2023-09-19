#include "catch.hpp"

#include "read.h"

#define CHECK_READ_TEST(v) do {CheckIsReadOk(#v, v); } while(false)

void CheckIsReadOk(const char* text, u32 value) {
  Big b = ReadBigNumber(text);
  REQUIRE((b.a << 16) + b.b == value);
}

TEST_CASE("My_first_test") {
  REQUIRE(1 == 1);
  REQUIRE(2 == 2);
  for (size_t i = 10; i < 100; ++i) {
    REQUIRE(i == i);
  }
}

TEST_CASE("My_second_test_it_fails") {
  CHECK_READ_TEST(66536);
  CHECK_READ_TEST(100);
  CHECK_READ_TEST(1024);
  CHECK_READ_TEST(999999999);
}
