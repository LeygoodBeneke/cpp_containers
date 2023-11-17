#include <vector>

#include "../s21_tests.h"

TEST(PushBackVector, Subtest_1) {
  s21::vector<int> own_vector;
  std::vector<int> default_vector;
  int a = 1;

  own_vector.push_back(a);
  default_vector.push_back(a);

  ASSERT_EQ(default_vector.capacity(), own_vector.capacity());
  ASSERT_EQ(default_vector.size(), own_vector.size());
}

TEST(PushBackVector, Subtest_2) {
  s21::vector<int> own_vector;
  std::vector<int> default_vector;
  const int a = 1;

  own_vector.push_back(a);
  default_vector.push_back(a);

  ASSERT_EQ(default_vector.capacity(), own_vector.capacity());
  ASSERT_EQ(default_vector.size(), own_vector.size());
}
