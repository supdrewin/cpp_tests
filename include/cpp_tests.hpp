#include <cstdio>
#include <list>

template <typename T> //
void assert_eq(T left, T right) {
  if (left != right)
    throw "failed";
}

template <typename T> //
void assert_ne(T left, T right) {
  if (left == right)
    throw "failed";
}

template <typename T = void()> //
struct Test {
  Test(T func, const char *name) //
      : name(name), run(func) {}
  const char *name;
  T *run;
};

class Tests {
public:
  Tests() : tests() {}

  void add(Test<> test) { tests.push_back(test); }

  template <typename T = void()> void add(T func, const char *name) {
    tests.push_back({func, name});
  }

  int run() {
    printf("running %zu tests\n", tests.size());
    for (auto test : tests) {
      printf("test %s ... ", test.name);
      try {
        test.run();
      } catch (const char *err) {
        printf("%s\n", err);
        return 1;
      }
      printf("ok\n");
    }
    return 0;
  }

private:
  std::list<Test<>> tests;
};
