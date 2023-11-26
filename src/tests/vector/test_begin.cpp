#include <vector>

#include "../s21_tests.h"

TEST(BeginVector, Subtest_1) {
  s21::vector<int> own_vector;
  ASSERT_EQ(own_vector.begin(), nullptr);
}

TEST(BeginVector, Subtest_2) {
  const s21::vector<int> own_vector;
  ASSERT_EQ(own_vector.begin(), nullptr);
}

TEST(BeginVector, Subtest_3) {
  s21::vector<int> own_vector;
  int a = 10;
  own_vector.push_back(a);
  own_vector.push_back(20);

  const s21::vector<int> own_vector_const(own_vector);

  ASSERT_EQ(*own_vector_const.begin(), 10);
  ASSERT_EQ(*(own_vector_const.end() - 1), 20);
}
