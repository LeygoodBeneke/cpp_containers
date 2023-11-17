#include <vector>

#include "../s21_tests.h"

TEST(InitialVector, Subtest_1) {
  s21::vector<int> own_vector;
  std::vector<int> default_vector;

  std::cout << default_vector.size() << '\n';
  std::cout << own_vector.size() << '\n';
}
