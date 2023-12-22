#include "../s21_tests.hpp"

TEST(InitialMultiset, Subtest_1) {
  s21::multiset<int> sss;
  int a = 2;
  sss.insert(a);
  ASSERT_EQ(sss.size(), 1);
  ASSERT_EQ(*sss.begin(), 2);
}

TEST(InitialMultiset2, Subtest_1) {
  s21::multiset<int> ss;
  std::multiset<int> ssd;
  s21::multiset<int>::iterator p = ss.insert(1);

  std::cout << "-- ITERATOR: " << *p << ' ' << *p << '\n';
}

TEST(InitialMultiset2, Subtest_2) {
  s21::multiset<int> ss;
  std::multiset<int> ssd;
  s21::multiset<int>::iterator p = ss.insert(25);
  ss.insert(30);

  ASSERT_EQ(ss.size(), 2);
}

TEST(InitialMultiset2, Subtest_3) {
  s21::multiset<int> ss;

  ss.insert(30);
  ss.insert(25);
  ss.insert(25);
  ss.insert(56);
  ss.insert(71);

  ASSERT_EQ(ss.size(), 5);
  s21::multiset<int>::iterator it = ss.begin();
  it++;
  ASSERT_EQ(*it, 25);
  it++;
  ASSERT_EQ(*it, 30);
  it++;
  ASSERT_EQ(*it, 56);
  it++;
  ASSERT_EQ(*it, 71);
  it++;
  ASSERT_EQ(it, ss.end());
}

TEST(InitialMultiset2, Subtest_4) {
  s21::multiset<int> ss;
  ss.insert(25);
  ss.insert(30);
  ss.insert(56);
  ss.insert(71);

  s21::multiset<int> ne(ss);

  ASSERT_EQ(ne.size(), ss.size());
  ASSERT_EQ(*ne.begin(), 25);
}

TEST(InitialMultiset2, Subtest_5) {
  const s21::multiset<int> ss = {1, 2, 3, 4};
  ASSERT_EQ(ss.size(), 4);
}

TEST(InitialMultiset2, Subtest_6) {
  s21::multiset<int> ss = {1, 2, 3, 4};
  ss.erase(ss.begin());
  ASSERT_EQ(ss.size(), 3);
  ASSERT_EQ(*ss.begin(), 2);
}

TEST(InitialMultiset2, Subtest_7) {
  s21::multiset<int> ss = {1, 2, 3, 4};
  s21::multiset<int> sss = {1, 2, 3};
  ss.swap(sss);
  ASSERT_EQ(ss.size(), 3);
  ASSERT_EQ(sss.size(), 4);
}

TEST(InitialMultiset2, Subtest_8) {
  s21::multiset<int> ss = {1, 2, 3, 4};
  s21::multiset<int> sss = {1, 2, 3};
  std::swap(sss, ss);
  ASSERT_EQ(ss.size(), 3);
  ASSERT_EQ(sss.size(), 4);
}

TEST(InitialMultiset2, Subtest_9) {
  s21::multiset<int> ss = {1, 2, 3, 4};
  s21::multiset<int> sss = {1, 2, 3};
  ASSERT_EQ(ss == sss, 0);
}

TEST(InitialMultiset2, Subtest_10) {
  s21::multiset<int> ss = {1, 2, 3, 3, 3, 3};
  s21::multiset<int> sss = {1, 2, 3, 3, 3};
  ASSERT_EQ(ss == sss, 0);
}
