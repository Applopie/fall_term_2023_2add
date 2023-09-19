#include <cstdint>

using u16 = uint16_t;
using u32 = uint32_t;

struct Big {
  u16 a, b;
  Big() : a(0), b(0) {}
};

Big ReadBigNumber(const std::string& s);
