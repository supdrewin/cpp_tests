#include <cstddef>
#include <cstdio>
#include <ctime>

template <typename T>           //
auto assert_eq(T left, T right) //
    -> void {
  if (left != right)
    throw "failed";
}

template <typename T>           //
auto assert_ne(T left, T right) //
    -> void {
  if (left == right)
    throw "failed";
}

template <typename T = void()> //
struct Test {
  Test(const char *name = nullptr, T *run = nullptr)
      : name(name), run(run), prev(nullptr), next(nullptr) {}
  auto operator==(Test test) //
      -> bool {
    return this->name == test.name //
           && this->run == test.run;
  }
  auto operator!=(Test test) //
      -> bool {
    return this->name != test.name //
           && this->run != test.run;
  }
  auto operator++() //
      -> Test & {
    auto self(this);
    self->name = next->name;
    self->run = next->run;
    self->prev = next->prev;
    self->next = next->next;
    return *self;
  }
  auto operator--() //
      -> Test & {
    auto self(this);
    self->name = prev->name;
    self->run = prev->run;
    self->prev = prev->prev;
    self->next = prev->next;
    return *self;
  }
  auto operator*() //
      -> Test {
    return *this;
  }
  const char *name;
  T *run;
  Test *prev;
  Test *next;
};

template <typename T = void()> //
class List {
public:
  List() : head(nullptr), tail(new Test<T>) {}

public:
  List(const List &list) //
      : head(list.head), tail(list.tail) {}

public:
  ~List() {
    if (this->head != nullptr) {
      auto test(this->head);
      while (test != this->tail) {
        delete this->head;
        test = test->next;
        this->head = test;
      }
    }
    delete this->tail;
  }

public:
  auto empty() //
      -> bool {
    return this->head == nullptr;
  }

public:
  auto size() //
      -> size_t {
    auto test(this->head);
    auto size(0);
    while (test != this->tail) {
      test = test->next;
      ++size;
    }
    return size;
  }

public:
  auto push_front(Test<T> *test) //
      -> void {
    if (this->head == nullptr) {
      this->head = test;
      this->head->prev = this->tail;
      this->tail->prev = this->head;
    } else {
      this->head->prev = test;
      test->prev = this->tail;
      test->next = this->head;
      this->head = test;
    }
  }

public:
  auto push_back(Test<T> *test) //
      -> void {
    if (this->head == nullptr) {
      this->head = test;
      this->head->prev = this->tail;
      this->tail->prev = this->head;
    } else {
      this->tail->prev->next = test;
      test->prev = this->tail->prev;
      this->tail->prev = test;
      test->next = this->tail;
    }
  }

public:
  auto pop_front() //
      -> void {
    if (this->head != nullptr) {
      auto test(this->head->next);
      delete this->head;
      this->head = nullptr;
      if (test != tail) {
        this->head = this->head->next;
        this->head->prev = tail;
      }
    }
  }

public:
  auto pop_back() //
      -> void {
    if (this->tail->prev == this->head) {
      delete this->head;
      this->head = nullptr;
    } else {
      auto test(this->tail->prev->prev);
      delete this->tail->prev;
      this->tail->prev = test;
      test->next = this->tail;
    }
  }

public:
  auto at(size_t idx) //
      -> Test<T> & {
    return this[idx];
  }

public:
  auto begin() //
      -> Test<T> & {
    return *this->head;
  }

public:
  auto cbegin() //
      -> Test<T> const & {
    return *this->head;
  }

public:
  auto rbegin() //
      -> Test<T> & {
    return *this->tail->prev;
  }

public:
  auto crbegin() //
      -> Test<T> const & {
    return *this->tail->prev;
  }

public:
  auto end() //
      -> Test<T> & {
    return *this->tail;
  }

public:
  auto cend() //
      -> Test<T> const & {
    return *this->tail;
  }

public:
  auto rend() //
      -> Test<T> & {
    return *this->head->prev;
  }

public:
  auto crend() //
      -> Test<T> const & {
    return *this->head->prev;
  }

public:
  auto operator[](size_t idx) //
      -> Test<T> & {
    auto test(this->head);
    while (test != this->tail //
           and idx > 0) {
      test = test->next;
      --idx;
    }
    return test;
  }

public:
  auto operator=(const List &list) //
      -> List & {
    this->head = list.head;
    this->tail = list.tail;
    return *this;
  }

private:
  Test<T> *head;

private:
  Test<T> *tail;
};

template <typename T = void()> //
class Tests {
public:
  Tests() : tests() {}

public:
  auto add(Test<T> *test) //
      -> void {
    this->tests.push_back(test);
  }

public:
  auto add(const char *name, T *run) //
      -> void {
    this->tests.push_back(new Test<T>(name, run));
  }

public:
  auto run() //
      -> int {
    printf("running %zu tests\n", this->tests.size());
    for (auto const &test : this->tests) {
      printf("test %s ... ", test.name);
      clock_t begin, end;
      try {
        begin = clock();
        test.run();
        end = clock();
      } catch (const char *err) {
        printf("%s\n", err);
        return 1;
      }
      printf("ok\t%04ld ms\n", //
             (end - begin) / 1000);
    }
    return 0;
  }

private:
  List<T> tests;
};
