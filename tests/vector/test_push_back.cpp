#include <vector>

#include "../proj_tests.hpp"

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

TEST(PushBackVector, Subtest_3) {
  s21::vector<int> own_vector;
  std::vector<int> default_vector;
  std::vector<int> addition_vector = {1, 2, 3, 4, 5, 6, 7, 8};

  for (auto value : addition_vector) {
    default_vector.push_back(value);
    own_vector.push_back(value);
  }

  for (size_t i = 0; i < addition_vector.size(); i++)
    ASSERT_EQ(default_vector[i], own_vector[i]);

  ASSERT_EQ(default_vector.capacity(), own_vector.capacity());
  ASSERT_EQ(default_vector.size(), own_vector.size());
}
