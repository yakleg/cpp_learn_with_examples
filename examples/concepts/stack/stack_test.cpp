#include <gtest/gtest.h>

class Foo {
 public:
  Foo() = default;
  Foo(int64_t a, int64_t b, int64_t c) : a{a}, b{b}, c{c} {};

 private:
  int64_t a;
  int64_t b;
  int64_t c;
  friend std::ostream& operator<<(std::ostream&, const Foo&);
};

std::ostream& operator<<(std::ostream& out, const Foo& a) {
  out << "Object A:{" << a.a << ", " << a.b << ", " << a.c << "}";
  return out;
}

// Allocates memory on stack for the instance of Foo
// and initialaze all the vales
void initialazeObject() { Foo foo{1, 2, 3}; }

// We allocate memory on stack for the array of tree int64_t
// and initialaze all the vales
void initialazeArray() { std::array<int64_t, 3>{100, 200, 300}; }

// Allocates memory on stack for the instance of Foo
// without initialization
void withoutInitialization(std::ostream& out) {
  Foo foo;
  out << foo << "\n";
}

// Target: to show how stack model works
TEST(stack_demonstration, set_data_with_class) {
  std::stringstream ss;

  // after call of this function Stack Pointer (SP)
  // will go up and left some data under SP
  initialazeObject();

  // when a new object initialized, all the values will take data left
  // on the stack from the previous function call
  withoutInitialization(ss);

  ASSERT_STREQ(ss.str().c_str(), "Object A:{1, 2, 3}\n");
}

TEST(stack_demonstration, set_data_with_array) {
  std::stringstream ss;

  // after call of this function Stack Pointer (SP)
  // will go up and left some data under SP
  initialazeArray();

  // when a new object initialized, all the values will take data left
  // on the stack from the previous function call
  withoutInitialization(ss);

  ASSERT_STREQ(ss.str().c_str(), "Object A:{100, 200, 300}\n");
}

TEST(stack_demonstration, uninitialazed_data) {
  std::stringstream ss;
  // when a new object initialized, all the values will take random data left on the stack
  withoutInitialization(ss);

  // Here we are faced with undefined behavior. Uninitialized scalar
  // see: https://en.cppreference.com/w/cpp/language/ub
  ASSERT_STRNE(ss.str().c_str(), "Object A:{1, 2, 3}\n");
  ASSERT_STRNE(ss.str().c_str(), "Object A:{100, 200, 300}\n");
}