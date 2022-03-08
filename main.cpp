#include "cpp_tests.hpp"

void test1() {
  auto src(0), dist(1 << 30);
  while (++src < dist) {
  }
  assert_eq(src, dist);
}

void test2() {
  auto src(1 << 30), dist(0);
  while (dist < src--) {
  }
  assert_ne(src, dist);
}

int main() {
  Tests<> tests;
  tests.add("test1", test1);
  tests.add("test2", test2);
  return tests.run();
}
