#include <gtest/gtest.h>

#include <iostream>
#include <string>

#include "../containers/multiset/s21_multiset.h"

TEST(Constructors, Default) {
  s21::multiset<int> ms;
  EXPECT_TRUE(ms.size() == 0);
}

TEST(Constructors, InitList) {
  s21::multiset<int> ms{1, 1, 1, 2, 2, 3, 3};
  EXPECT_TRUE(ms.size() == 7);
}

TEST(Constructors, Copy) {
  s21::multiset<int> ms{1, 1, 1, 2, 2, 3, 3};
  s21::multiset<int> ms2(s);
  EXPECT_TRUE(ms2 == ms);
}

TEST(Constructors, Move) {
  s21::multiset<int> ms{1, 1, 1, 2, 2, 3, 3};
  s21::multiset<int> ms2(std::move(s));
  EXPECT_TRUE(ms.size() == 7);
}

TEST(Operator, Assign) {
  s21::multiset<int> ms{1, 2, 3};
  s21::multiset<int> ms2;
  ms2 = ms;
  EXPECT_TRUE(ms2 == ms);
}

TEST(Methods, Size) {
  s21::multiset<int> ms;
  s21::multiset<int> ms2{1, 2, 3};
  s21::multiset<int> ms3{1, 1, 1, 2, 2, 3, 3};
  EXPECT_TRUE(ms.size() == 0);
  EXPECT_TRUE(ms2.size() == 3);
  EXPECT_TRUE(ms3.size() == 7);
}

TEST(Methods, Empty) {
  s21::multiset<int> ms;
  s21::multiset<int> ms2{1, 1, 1, 2, 2, 3, 3};
  EXPECT_EQ(ms.empty(), true);
  EXPECT_EQ(ms2.empty(), false);
}

TEST(Methods, Clear) {
  s21::multiset<int> ms{1, 2, 3};
  ms.clear();
  EXPECT_EQ(ms.empty(), true);
}

TEST(Methods, Erase) {
  s21::multiset<int> ms{1, 1, 1, 2, 2, 3, 3};
  ms.erase(ms.begin());
  EXPECT_EQ(ms.size(), 6);
  EXPECT_EQ(*ms.begin(), 1);
}

TEST(Methods, Swap) {
  s21::multiset<int> ms{1, 1, 1, 2, 2, 3, 3};
  s21::multiset<int> ms2{4, 5, 6, 7};
  ms.swap(ms2);
  EXPECT_EQ(ms.size(), 4);
  EXPECT_EQ(ms2.size(), 7);
  EXPECT_EQ(*ms.begin() 1);
  EXPECT_EQ(*ms2.begin(), 4);
}

TEST(Methods, Begin) {
  s21::multiset<int> ms{1, 1, 1, 2, 2, 3, 3};
  s21::multiset<int> ms2{4, 5, 6, 7};
  EXPECT_EQ(*ms.begin() 1);
  EXPECT_EQ(*ms2.begin(), 4);
  EXPECT_EQ(*(++ms.begin()) 1);
  EXPECT_EQ(*(++ms2.begin()), 5);
}

TEST(Methods, End) {
  s21::multiset<int> ms{1, 1, 1, 2, 2, 3, 3};
  s21::multiset<int> ms2{4, 5, 6, 7};
  EXPECT_EQ(*(--ms.end()), 3);
  EXPECT_EQ(*(--ms2.end()), 6);
}

TEST(Methods, Merge) {
  s21::multiset<int> ms{1, 1, 1, 2, 2, 3, 3};
  s21::multiset<int> ms2{4, 5, 6, 7};
  ms.merge(ms2);
  EXPECT_EQ(ms.size(), 11);
  EXPECT_EQ(*(--ms.end()), 7);
  EXPECT_EQ(*ms.begin(), 1);
}

TEST(Methods, Count) {
  s21::multiset<int> ms{1, 1, 1, 2, 2, 3, 3};
  EXPECT_EQ(ms.count(1), 3);
  EXPECT_EQ(ms.count(2), 2);
  EXPECT_EQ(ms.count(3), 2);
}

TEST(Methods, Find) {
  s21::multiset<int> ms{1, 2, 2, 3};
  EXPECT_EQ(ms.find(1), ms.begin());
  EXPECT_EQ(ms.find(3), --ms.end());
}

TEST(Methods, Contains) {
  s21::multiset<int> ms{1, 2, 2, 3};
  EXPECT_EQ(ms.contains(1), true);
  EXPECT_EQ(ms.contains(4), false);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
