#include <algorithm>
#include <vector>
#include <iterator>

#include <gtest/gtest.h>

const int c_array[] = {9, 81, 7, 6, -20, 4, 3, 12, 1, -2, 23, 40};

// The purpose of this ... id to show the problems of usage C arrays
// and to show the right way to deal with it.

// There is no way to write something like that:
// int GetMin(int array[]) {    // comliler can't know the size of array and int
// array[] becomes int *array
//  for (auto&& x : a) {}       // comliler must know the size of array
// }

// This is also a wrong way to use pure c arrays
// int GetMin(int array[]) {                        // the same as in the
// previous example
//  while (a != 0) { int item = *a; ++a;}           // here we will go beyond
//  array borders (undefined behavior)
// }

// !!!!!!!!   DRAFT   !!!!!!!
// The right way 
namespace {

#if __cplusplus > 201703L
// Todo: implement when C++ 20 comes
int GetMin(std::span<int> array);
#endif

int GetMin(const std::vector<int>& vct) {
  auto it = std::min_element(vct.begin(), vct.end());
  return *it;
}

}  // namespace

TEST(c_arrays, pure_c_array_usage) {
  const int expected = -20;

  auto vct = std::vector<int>(std::begin(c_array), std::end(c_array));

  int min = GetMin(vct);

  ASSERT_EQ(min, expected);
}