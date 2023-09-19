// REQUIRE
// TEST_CASE

#include <map>
#include <string>
#include <cstdint>

using u32 = uint32_t;

struct TestRegistry {
  static TestRegistry& GetInstance() {
    static TestRegistry registry;
    return registry;
  }

  using TestFunction = void(*)();

  TestRegistry() : num_test_cases(0),
                   num_checks(0),
                   num_checks_ok(0) {}

  void AddTest(const char* test_name, TestFunction v) {
    tests[test_name] = v;
    num_test_cases ++;
  }

  static bool AddTestS(const char* test_name, TestFunction v) {
    GetInstance().AddTest(test_name, v);
    return true;
  }

  void RunAll() {
    for (auto& p : tests) {
      p.second();
    }

    std::cerr << "Total:  " << num_checks << " in " << num_test_cases << " tests\n";
    std::cerr << "Passed: " << num_checks_ok << "\n";
  }
  
  u32 num_test_cases, num_checks, num_checks_ok;
  std::map<std::string, TestFunction> tests;
};


#define CONCAT_I(x, y)  x##y
#define CONCAT(x, y) CONCAT_I(x, y)

#define TEST_CASE(name)                         \
  TEST_CASE_INTERNAL(name, __COUNTER__)

#define TEST_CASE_INTERNAL(name, ctr)           \
  void CONCAT(Test, ctr) ();                     \
  namespace { \
    static bool CONCAT(registered, ctr) = TestRegistry::AddTestS(name, CONCAT(Test, ctr)); \
  }\
  void CONCAT(Test, ctr) ()



bool Require(const char* expression,
             const char* filename,
             int line,
             bool value) {
  TestRegistry::GetInstance().num_checks ++;
  if (!value) {
    std::cerr << "In file " << filename << ":" << line << "\n";
    std::cerr << "\tTest failed:\n";
    std::cerr << "\tREQUIRE ( " << expression << " )\n";
  } else {
    TestRegistry::GetInstance().num_checks_ok ++;  
  }
  return value;
}

#define REQUIRE(value)                                          \
  do {                                                          \
    bool v = Require(#value, __FILE__, __LINE__,  (value));     \
    if (!v) return;                                             \
  } while(false)


int main() {
  TestRegistry& r = TestRegistry::GetInstance();
  /*  r.AddTest("Test1", Test1);
      r.AddTest("Test2", Test2);*/
  r.RunAll();
}
