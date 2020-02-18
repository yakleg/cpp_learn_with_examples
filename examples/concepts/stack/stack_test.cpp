#include <gtest/gtest.h>

class A {
 public:
  A() = default;
  A(int64_t a, int64_t b, int64_t c) : a{a}, b{b}, c{c} {};

 private:
  int64_t a;
  int64_t b;
  int64_t c;
  friend std::ostream& operator<<(std::ostream&, const A&);
};

std::ostream& operator<<(std::ostream& out, const A& a) {
  out << "Object A:{" << a.a << ", " << a.b << ", " << a.c << "}";
  return out;
}

void initialazeObject() { A a{1, 2, 3}; }

void initialazeArray() { std::array<int64_t, 3>{100, 200, 300}; }

void withoutInitialization(std::ostream& out) {
  A a;
  out << a << "\n";
}

TEST(stack_demonstration, set_data_with_class) {
  std::stringstream ss;

  initialazeObject();
  withoutInitialization(ss);

  ASSERT_STREQ(ss.str().c_str(), "Object A:{1, 2, 3}\n");
}

TEST(stack_demonstration, set_data_with_array) {
  std::stringstream ss;

  initialazeArray();
  withoutInitialization(ss);

  ASSERT_STREQ(ss.str().c_str(), "Object A:{100, 200, 300}\n");
}