#include <vector>

#include "../s21_tests.h"

TEST(ScopeOperatorVector, Subtest_1) {
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

TEST(ScopeOperatorVector, Subtest_2) {
  s21::vector<int> own_vector(20);
  for (size_t i = 0; i < 20; i++) own_vector[i] = i;

  for (size_t i = 0; i < 20; i++) ASSERT_EQ(own_vector[i], i);
}

TEST(ScopeOperatorVector, Subtest_3) {
  std::initializer_list<int> ilist = {0, 1, 2, 3};
  s21::vector<int> own_vector(ilist);
  const s21::vector<int> own_vector_const(own_vector);
  for (size_t i = 0; i < 4; i++) ASSERT_EQ(own_vector_const[i], i);
}
