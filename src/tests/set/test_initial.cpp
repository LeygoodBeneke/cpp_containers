#include "../s21_tests.h"

TEST(InitialSet, Subtest_1) {
  s21::set<int> sss;
  const int a = 2;
  sss.insert(a);
}

TEST(InitialSet2, Subtest_1) {
  s21::set<int> ss;
  std::set<int> ssd;
  std::pair<s21::set<int>::iterator, bool> p = ss.insert(1);
  std::pair<std::set<int>::iterator, bool> pd = ssd.insert(1);

  std::cout << "-- ITERATOR: " << *p.first << ' ' << p.second << '\n';
  std::cout << "++ ITERATOR: " << *pd.first << ' ' << pd.second << '\n';
}
