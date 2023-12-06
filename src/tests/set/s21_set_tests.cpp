#include <gtest/gtest.h>

#include <iostream>
#include <string>

#include "../containers/set/s21_set.h"

TEST(Constructors, Default) {
  s21::set<int> s;
  EXPECT_TRUE(s.size() == 0);
}

TEST(Constructors, InitList) {
  s21::set<int> s{1, 2, 3};
  EXPECT_TRUE(s.size() == 3);
}

TEST(Constructors, Copy) {
  s21::set<int> s{1, 2, 3};
  s21::set<int> s2(s);
  EXPECT_TRUE(s2 == s);
}

TEST(Constructors, Move) {
  s21::set<int> s{1, 2, 3};
  s21::set<int> s2(std::move(s));
  EXPECT_TRUE(s2.size() == 3);
}

TEST(Operator, Assign) {
  s21::set<int> s{1, 2, 3};
  s21::set<int> s2;
  s2 = s;
  EXPECT_TRUE(s2 == s);
}

TEST(Methods, Size) {
  s21::set<int> s;
  s21::set<int> s2{1, 2, 3};
  s21::set<int> s3{1, 2, 3, 4, 5};
  EXPECT_TRUE(s.size() == 0);
  EXPECT_TRUE(s2.size() == 3);
  EXPECT_TRUE(s3.size() == 5);
}

TEST(Methods, Empty) {
  s21::set<int> s;
  s21::set<int> s2{1, 2, 3};
  EXPECT_EQ(s.empty(), true);
  EXPECT_EQ(s2.empty(), false);
}

TEST(Methods, Insert) {
  s21::set<int> s{1, 2, 3};
  bool status = s.insert(5);
  EXPECT_EQ(status, true);
  status = s.insert(1);
  EXPECT_EQ(status, false);
}

TEST(Methods, Clear) {
  s21::set<int> s{1, 2, 3};
  s.clear();
  EXPECT_EQ(s.empty(), true);
}

TEST(Methods, Erase) {
  s21::set<int> s{1, 2, 3};
  s.erase(s.begin());
  EXPECT_EQ(s.size(), 2);
  EXPECT_EQ(*s.begin(), 2);
}

TEST(Methods, Swap) {
  s21::set<int> s{1, 2, 3};
  s21::set<int> s2{4, 5, 6, 7};
  s.swap(s2);
  EXPECT_EQ(s.size(), 3);
  EXPECT_EQ(s2.size(), 4);
  EXPECT_EQ(*s.begin() 4);
  EXPECT_EQ(*s2.begin(), 1);
}

TEST(Methods, Begin) {
  s21::set<int> s{1, 2, 3};
  s21::set<int> s2{4, 5, 6, 7};
  EXPECT_EQ(*s.begin() 1);
  EXPECT_EQ(*s2.begin(), 4);
  EXPECT_EQ(*(++s.begin()) 2);
  EXPECT_EQ(*(++s2.begin()), 5);
}

TEST(Methods, End) {
  s21::set<int> s{1, 2, 3};
  s21::set<int> s2{4, 5, 6, 7};
  EXPECT_EQ(s.size(), 3);
  EXPECT_EQ(s2.size(), 4);
  EXPECT_EQ(*(--s.end()), 3);
  EXPECT_EQ(*(--s2.end()), 7);
}

TEST(Methods, Merge) {
  s21::set<int> s{1, 2, 3};
  s21::set<int> s2{4, 5, 6, 7};
  s.merge(s2);
  EXPECT_EQ(s.size(), 7);
  EXPECT_EQ(*(--s.end()), 7);
  EXPECT_EQ(*s.begin(), 1);
}

TEST(Methods, Find) {
  s21::set<int> s{1, 2, 3};
  EXPECT_EQ(s.find(1), s.begin());
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
