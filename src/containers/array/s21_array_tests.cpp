#include <gtest/gtest.h>

#include <iostream>

#include "s21_array.hpp"

TEST(Constructors, Default) {
  s21::array<int, 5> a;
  EXPECT_EQ(a.size(), 5);
}

TEST(Constructors, Copy) {
  s21::array<int, 5> a = {1, 2, 3, 4, 5};
  s21::array<int, 5> a2(a);
  EXPECT_TRUE(a2.size() == 5);
  EXPECT_TRUE(a == a2);
}

TEST(Constructors, Move) {
  s21::array<int, 5> a{1, 2, 3, 4, 5};
  s21::array<int, 5> a2(std::move(a));
  s21::array<int, 5> a3{1, 2, 3, 4, 5};
  EXPECT_TRUE(a2.size() == 5);
  EXPECT_TRUE(a2 == a3);
}

TEST(Constructors, InitList) {
  s21::array<int, 5> a{1, 2, 3, 4, 5};
  EXPECT_EQ(a.size(), 5);
  EXPECT_EQ(a.front(), 1);
  EXPECT_EQ(a.back(), 5);
}

TEST(Constructors, AssignOperator) {
  s21::array<int, 5> a{1, 2, 3, 4, 5};
  s21::array<int, 5> a2 = a;
  EXPECT_EQ(a2.size(), 5);
  EXPECT_TRUE(a2 == a);
}

TEST(Constructors, MoveOperator) {
  s21::array<int, 5> a{1, 2, 3, 4, 5};
  s21::array<int, 5> a2 = std::move(a);
  EXPECT_EQ(a2.size(), 5);
  EXPECT_EQ(a2.front(), 1);
  EXPECT_EQ(a2.back(), 5);
}
TEST(Operators, Index) {
  s21::array<int, 5> a{1, 2, 3, 4, 5};
  EXPECT_EQ(a[0], 1);
  EXPECT_EQ(a[1], 2);
  EXPECT_EQ(a[2], 3);
  EXPECT_EQ(a[3], 4);
  EXPECT_EQ(a[4], 5);
}

TEST(Methods, At) {
  s21::array<int, 5> a{1, 2, 3, 4, 5};
  a.at(4) = 9;
  EXPECT_EQ(a.size(), 5);
  EXPECT_EQ(a.at(4), 9);
  a.at(4) = a.at(2);
  EXPECT_EQ(a.at(4), 3);
}

TEST(Methods, Front) {
  s21::array<int, 5> a{1, 2, 3, 4, 5};
  EXPECT_EQ(a.front(), 1);
  a.at(0) = 9;
  EXPECT_EQ(a.front(), 9);
}

TEST(Methods, Back) {
  s21::array<int, 5> a{1, 2, 3, 4, 5};
  EXPECT_EQ(a.back(), 5);
  a.at(4) = 9;
  EXPECT_EQ(a.back(), 9);
}

TEST(Methods, Data) {
  s21::array<int, 5> a{1, 2, 3, 4, 5};
  EXPECT_EQ(a.data(), a.begin());
}

TEST(Methods, Begin) {
  s21::array<int, 5> a{1, 2, 3, 4, 5};
  EXPECT_EQ(*a.begin(), 1);
}

TEST(Methods, End) {
  s21::array<int, 5> a{1, 2, 3, 4, 5};
  EXPECT_EQ(*(a.end() - 1), 5);
}

TEST(Methods, Empty) {
  s21::array<int, 5> a{1, 2, 3, 4, 5};
  EXPECT_EQ(a.empty(), false);
}

TEST(Methods, Size) {
  s21::array<int, 5> a{1, 2, 3, 4, 5};
  EXPECT_EQ(a.size(), 5);
}

TEST(Methods, MaxSize) {
  s21::array<int, 5> a{1, 2, 3, 4, 5};
  EXPECT_EQ(a.max_size(), 5);
}

TEST(Methods, Swap) {
  s21::array<int, 5> a{1, 2, 3, 4, 5};
  s21::array<int, 5> a2{6, 7, 8, 9, 10};
  a2.swap(a);
  EXPECT_EQ(a.front(), 6);
  EXPECT_EQ(a2.front(), 1);
  EXPECT_EQ(a.back(), 10);
  EXPECT_EQ(a2.back(), 5);
}

TEST(Methods, Fill) {
  s21::array<int, 5> a{1, 2, 3, 4, 5};
  s21::array<int, 5> a2{6, 6, 6, 6, 6};
  a.fill(6);
  EXPECT_TRUE(a == a2);
}

TEST(Specialization, Zero) {
  s21::array<int, 0> a;
  EXPECT_EQ(a.size(), 0);
  EXPECT_EQ(a.max_size(), 0);
  EXPECT_EQ(a.empty(), true);
  s21::array<int, 0> a2;
  a.swap(a2);
  EXPECT_EQ(a2.size(), 0);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
