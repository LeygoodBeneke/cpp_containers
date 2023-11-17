#include <vector>

#include "../s21_tests.h"

TEST(ExceptionVector, Subtest_1) {
  s21::vector<int> own_vector;
  own_vector.push_back(20);
  bool flag = false;
  try {
    std::cout << own_vector[3];
  } catch (...) {
    flag = true;
  }

  ASSERT_TRUE(flag);
}
