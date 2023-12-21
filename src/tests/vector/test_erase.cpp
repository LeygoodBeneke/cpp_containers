#include <vector>

#include "../s21_tests.hpp"

TEST(EraseVector, Subtest_1) {
  s21::vector<int> own_vector;
  std::vector<int> default_vector;
  const int a = 1;

  own_vector.push_back(a);
  default_vector.push_back(a);
  own_vector.erase(own_vector.begin());
  default_vector.erase(default_vector.begin());

  ASSERT_EQ(default_vector.capacity(), own_vector.capacity());
  ASSERT_EQ(default_vector.size(), own_vector.size());
}

TEST(EraseVector, Subtest_2) {
  s21::vector<int> own_vector;
  std::vector<int> default_vector;
  std::vector<int> addition_vector = {1, 2, 3, 4, 5, 6, 7, 8};

  for (auto value : addition_vector) {
    default_vector.push_back(value);
    own_vector.push_back(value);
  }

  own_vector.erase(own_vector.begin() + 1);
  default_vector.erase(default_vector.begin() + 1);

  for (size_t i = 0; i < addition_vector.size() - 1; i++)
    ASSERT_EQ(default_vector[i], own_vector[i]);

  ASSERT_EQ(default_vector.capacity(), own_vector.capacity());
  ASSERT_EQ(default_vector.size(), own_vector.size());
}
