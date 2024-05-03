#include <vector>

#include "../proj_tests.hpp"

TEST(SwapVector, Subtest_1) {
  s21::vector<int> own_vector;
  std::vector<int> default_vector;

  std::vector<int> sw1 = {1, 2, 3};
  s21::vector<int> sw2 = {1, 2, 3};

  own_vector.swap(sw2);
  default_vector.swap(sw1);

  for (size_t i = 0; i < 3; i++) ASSERT_EQ(own_vector[i], default_vector[i]);

  ASSERT_EQ(default_vector.capacity(), own_vector.capacity());
  ASSERT_EQ(default_vector.size(), own_vector.size());
}
