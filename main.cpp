#include "cpp_tests.hpp"

void test1() { assert_eq(1, 1); }
void test2() { assert_ne(1, 2); }
void test3() { assert_eq(2, 1); }

int main() {
  Tests tests;
  tests.add(test1, "test1");
  tests.add(test2, "test2");
  tests.add(test3, "test3");
  return tests.run();
}
