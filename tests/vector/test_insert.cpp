#include <vector>

#include "../proj_tests.hpp"

TEST(InsertVector, Subtest_1) {
  s21::vector<int> own_vector = {1};
  std::vector<int> default_vector = {1};
  int a = 1;

  for (int i = 0; i < 3; i++) {
    own_vector.insert(own_vector.begin(), a);
    default_vector.insert(default_vector.begin(), a);
    a *= 2;
  }

  for (size_t i = 0; i < 4; i++) ASSERT_EQ(own_vector[i], default_vector[i]);

  ASSERT_EQ(default_vector.capacity(), own_vector.capacity());
  ASSERT_EQ(default_vector.size(), own_vector.size());
}

TEST(InsertVector, Subtest_2) {
  s21::vector<int> own_vector;
  std::vector<int> default_vector;
  int a = 1;

  for (int i = 0; i < 3; i++) {
    own_vector.insert(own_vector.begin(), a);
    default_vector.insert(default_vector.begin(), a);
    a *= 2;
  }

  for (size_t i = 0; i < 3; i++) ASSERT_EQ(own_vector[i], default_vector[i]);

  ASSERT_EQ(default_vector.capacity(), own_vector.capacity());
  ASSERT_EQ(default_vector.size(), own_vector.size());
}

TEST(InsertVector, Subtest_3) {
  s21::vector<int> own_vector(3);
  std::vector<int> default_vector(3);
  ASSERT_EQ(default_vector.capacity(), own_vector.capacity());
  ASSERT_EQ(default_vector.size(), own_vector.size());
}
