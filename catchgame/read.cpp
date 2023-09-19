#include <iostream>
#include <string>
#include "read.h"

void Print(Big n) { std::cout << "[" << n.a << ", " << n.b << "]\n"; }

Big ReadBigNumber(const std::string& s) {
  Big big;

  const u16 u16_max = static_cast<u16>(-1);
  const u16 limit = u16_max / 10;

  /*
  std::string s = "66535";
  std::cin >> s;*/

  for (size_t i = 0; i < s.length(); ++i) {
    u16 tmp_a = 0, tmp_b = 0;
    tmp_a = big.b >> 14;
    tmp_b = big.b << 2;

    if (big.b > u16_max - tmp_b) {
      tmp_a += 1;
    }

    big.b = big.b + tmp_b;
    //    Print(big);
    tmp_a <<= 1;
    tmp_a += (big.b >> 15);
    big.b <<= 1;
    big.a = big.a * 10 + tmp_a;
    
    u16 cur_digit = s[i] - '0';
    if (big.b > u16_max - cur_digit) {
      ++big.a;
    }
    big.b += cur_digit;

    //std::cout << "// In progress... a=" << big.a << ", b=" << big.b << "\n";
  }

  return big;
  // std::cout << s;
}
/*
int main() {
  auto big = ReadBigNumber();
  u32 t = big.a;
  t <<= 16;
  t += big.b;
  std::cout << "RESULT: " << t << "\n";
}
*/
