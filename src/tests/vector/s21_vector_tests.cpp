#include <vector>

#include "../s21_tests.hpp"

TEST(InsertManyVector, Subtest_1) {
  s21::vector<int> own_vector({1, 2, 3});
  s21::vector<int>::const_iterator it = own_vector.begin();
  it++;
  try {
    own_vector.insert_many(it, 10, 20, 30, 40, 50);

  } catch (std::exception &e) {
    std::cout << e.what() << '\n';
  }

  std::vector<int> answer = {1, 10, 20, 30, 40, 50, 2, 3};
  for (std::size_t i = 0; i < answer.size(); i++) {
    ASSERT_EQ(answer[i], own_vector[i]);
  }
}

TEST(InsertManyBackVector, Subtest_1) {
  s21::vector<int> own_vector({1, 2, 3});
  s21::vector<int>::const_iterator it = own_vector.begin();
  it++;
  try {
    own_vector.insert_many_back(10, 20, 30, 40, 50);

  } catch (std::exception &e) {
    std::cout << e.what() << '\n';
  }

  std::vector<int> answer = {1, 2, 3, 10, 20, 30, 40, 50};
  for (std::size_t i = 0; i < answer.size(); i++) {
    ASSERT_EQ(answer[i], own_vector[i]);
  }
}
