#include <gtest/gtest.h>

#include <iostream>

#include "s21_queue.hpp"

TEST(Constructors, Default) {
  s21::queue<int> q;
  EXPECT_TRUE(q.size() == 0);
}

TEST(Constructors, InitList) {
  s21::queue<int> q{1, 2, 3, 4};
  EXPECT_TRUE(q.size() == 4);
  EXPECT_TRUE(q.front() == 1);
  EXPECT_TRUE(q.back() == 4);
}

TEST(Constructors, Copy) {
  s21::queue<int> q{1, 2, 3, 4};
  s21::queue<int> q2(q);
  EXPECT_TRUE(q == q2);
}

TEST(Constructors, Move) {
  s21::queue<int> q{1, 2, 3, 4};
  s21::queue<int> q2(std::move(q));
  EXPECT_TRUE(q2.size() == 4);
  EXPECT_TRUE(q2.back() == 4);
}

TEST(Methods, Size) {
  s21::queue<int> q{1};
  s21::queue<int> q2{1, 2};
  s21::queue<int> q3{1, 2, 3};
  EXPECT_TRUE(q.size() == 1);
  EXPECT_TRUE(q2.size() == 2);
  EXPECT_TRUE(q3.size() == 3);
}

TEST(Methods, Empty) {
  s21::queue<int> q{1};
  s21::queue<int> q2;
  EXPECT_TRUE(q.empty() == false);
  EXPECT_TRUE(q2.empty() == true);
}

TEST(Methods, Assign) {
  s21::queue<int> q{1};
  s21::queue<int> q2 = q;
  EXPECT_TRUE(q.size() == 1);
  EXPECT_TRUE(q2.front() == 1);
}

TEST(Methods, Front) {
  s21::queue<int> q{1, 2, 3, 4};
  EXPECT_TRUE(q.front() == 1);
  q.front() = 5;
  EXPECT_TRUE(q.front() == 5);
}

TEST(Methods, Back) {
  s21::queue<int> q{1, 2, 3, 4};
  EXPECT_TRUE(q.back() == 4);
  q.back() = 5;
  EXPECT_TRUE(q.back() == 5);
}

TEST(Methods, Push) {
  s21::queue<int> q{1, 2, 3, 4};
  q.push(5);
  EXPECT_TRUE(q.back() == 5);
  q.push(6);
  EXPECT_TRUE(q.back() == 6);
  q.push(7);
  EXPECT_TRUE(q.back() == 7);
}

TEST(Methods, Pop) {
  s21::queue<int> q{1, 2, 3, 4};
  q.pop();
  EXPECT_TRUE(q.front() == 2);
  q.pop();
  EXPECT_TRUE(q.front() == 3);
  q.pop();
  EXPECT_TRUE(q.front() == 4);
}

TEST(Methods, Swap) {
  s21::queue<int> q{1, 2, 3, 4};
  s21::queue<int> q2{5, 6};
  q.swap(q2);
  EXPECT_TRUE(q.back() == 6);
  EXPECT_TRUE(q2.back() == 4);
  EXPECT_TRUE(q.size() == 2);
  EXPECT_TRUE(q2.size() == 4);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
