#include <vector>

#include "../s21_tests.h"

TEST(InitialVector, Subtest_1) {
  s21::vector<int> own_vector;
  std::vector<int> default_vector;

  ASSERT_EQ(default_vector.capacity(), own_vector.capacity());
  ASSERT_EQ(default_vector.size(), own_vector.size());
}

TEST(InitialVector, Subtest_2) {
  s21::vector<int> own_vector({1, 2, 3});
  std::vector<int> default_vector({1, 2, 3});

  for (size_t i = 0; i < 3; i++) ASSERT_EQ(default_vector[i], own_vector[i]);
  ASSERT_EQ(default_vector.capacity(), own_vector.capacity());
  ASSERT_EQ(default_vector.size(), own_vector.size());
}

TEST(InitialVector, Subtest_3) {
  s21::vector<int> own_vector = {1, 2, 3};
  std::vector<int> default_vector = {1, 2, 3};

  for (size_t i = 0; i < 3; i++) ASSERT_EQ(default_vector[i], own_vector[i]);
  ASSERT_EQ(default_vector.capacity(), own_vector.capacity());
  ASSERT_EQ(default_vector.size(), own_vector.size());
}

TEST(InitialVector, Subtest_4) {
  s21::vector<int> own_vector{1, 2, 3};
  std::vector<int> default_vector{1, 2, 3};

  for (size_t i = 0; i < 3; i++) ASSERT_EQ(default_vector[i], own_vector[i]);
  ASSERT_EQ(default_vector.capacity(), own_vector.capacity());
  ASSERT_EQ(default_vector.size(), own_vector.size());
}
