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

template <typename T> //
struct Test {
  Test(T func, const char *name) //
      : name(name), run(func) {}
  const char *name;
  T *run;
};

template <typename T = void()> //
class Tests {
public:
  Tests() : tests() {}

  void add(T func, const char *name) { tests.push_back({func, name}); }
  void add(Test<T> test) { tests.push_back(test); }

  int run() {
    printf("running %zu tests\n", tests.size());
    for (auto test : tests) {
      printf("test %s ... ", test.name);
      try {
        test.run();
      } catch (const char *str) {
        printf("%s\n", str);
        return 1;
      }
      printf("ok\n");
    }
    return 0;
  }

private:
  std::list<Test<T>> tests;
};
