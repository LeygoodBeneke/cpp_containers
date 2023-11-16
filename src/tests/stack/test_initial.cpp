#include <stack>

#include "../s21_tests.h"

TEST(InitialStack, Subtest_1) {
  s21::stack<int> a;

  std::stack<int> st;
  st.pop();

  std::cout << (st.size() == UINT64_MAX) << '\n';
}
