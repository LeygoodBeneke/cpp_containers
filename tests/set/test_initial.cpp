#include "../proj_tests.hpp"

TEST(InitialSet, Subtest_1) {
  s21::set<int> sss;
  int a = 2;
  sss.insert(a);
  ASSERT_EQ(sss.size(), 1);
  ASSERT_EQ(*sss.begin(), 2);
}

TEST(InitialSet2, Subtest_1) {
  s21::set<int> ss;
  std::set<int> ssd;
  std::pair<s21::set<int>::iterator, bool> p = ss.insert(1);
  std::pair<std::set<int>::iterator, bool> pd = ssd.insert(1);

  std::cout << "-- ITERATOR: " << *p.first << ' ' << p.second << '\n';
  std::cout << "++ ITERATOR: " << *pd.first << ' ' << pd.second << '\n';
}

TEST(InitialSet2, Subtest_2) {
  s21::set<int> ss;
  std::set<int> ssd;
  std::pair<s21::set<int>::iterator, bool> p = ss.insert(25);
  ss.insert(30);

  ASSERT_EQ(ss.size(), 2);
}

TEST(InitialSet2, Subtest_3) {
  s21::set<int> ss;

  ss.insert(30);
  ss.insert(25);
  ss.insert(56);
  ss.insert(71);

  ASSERT_EQ(ss.size(), 4);
  s21::set<int>::iterator it = ss.begin();
  it++;
  ASSERT_EQ(*it, 30);
  it++;
  ASSERT_EQ(*it, 56);
  it++;
  ASSERT_EQ(*it, 71);
  it++;
  ASSERT_EQ(it, ss.end());
}

TEST(InitialSet2, Subtest_4) {
  s21::set<int> ss;
  ss.insert(25);
  ss.insert(30);
  ss.insert(56);
  ss.insert(71);

  s21::set<int> ne(ss);

  ASSERT_EQ(ne.size(), ss.size());
  ASSERT_EQ(*ne.begin(), 25);
}

TEST(InitialSet2, Subtest_5) {
  const s21::set<int> ss = {1, 2, 3, 4};
  ASSERT_EQ(ss.size(), 4);
}

TEST(InitialSet2, Subtest_6) {
  s21::set<int> ss = {1, 2, 3, 4};
  ss.erase(ss.begin());
  ASSERT_EQ(ss.size(), 3);
  ASSERT_EQ(*ss.begin(), 2);
}

TEST(InitialSet2, Subtest_7) {
  s21::set<int> ss = {1, 2, 3, 4};
  s21::set<int> sss = {1, 2, 3};
  ss.swap(sss);
  ASSERT_EQ(ss.size(), 3);
  ASSERT_EQ(sss.size(), 4);
}

TEST(InitialSet2, Subtest_8) {
  s21::set<int> ss = {1, 2, 3, 4};
  s21::set<int> sss = {1, 2, 3};
  std::swap(sss, ss);
  ASSERT_EQ(ss.size(), 3);
  ASSERT_EQ(sss.size(), 4);
}

TEST(InitialSet2, Subtest_9) {
  s21::set<int> ss = {1, 2, 3, 4};
  s21::set<int> sss = {1, 2, 3};
  ASSERT_EQ(ss == sss, 0);
}

TEST(InitialSet2, Subtest_10) {
  s21::set<int> ss = {1, 2, 3};
  s21::set<int> sss = {1, 2, 3};
  ASSERT_EQ(ss == sss, 1);
}
