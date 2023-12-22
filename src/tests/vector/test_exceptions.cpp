#include <vector>

#include "../s21_tests.hpp"

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

TEST(ExceptionVector, Subtest_2) {
  s21::vector<int> own_vector = {};
  bool flag = false;
  try {
    own_vector.pop_back();
  } catch (...) {
    flag = true;
  }

  ASSERT_TRUE(flag);
}
