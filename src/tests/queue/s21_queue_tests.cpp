#include "../s21_tests.h"

TEST(QueueConstructors, Default) {
  s21::queue<int> q;
  EXPECT_TRUE(q.size() == 0);
}

TEST(QueueConstructors, InitList) {
  s21::queue<int> q{1, 2, 3, 4};
  EXPECT_TRUE(q.size() == 4);
  EXPECT_TRUE(q.front() == 1);
  EXPECT_TRUE(q.back() == 4);
}

TEST(QueueConstructors, Copy) {
  s21::queue<int> q{1, 2, 3, 4};
  s21::queue<int> q2(q);
  EXPECT_TRUE(q == q2);
}

TEST(QueueConstructors, Move) {
  s21::queue<int> q{1, 2, 3, 4};
  s21::queue<int> q2(std::move(q));
  EXPECT_TRUE(q2.size() == 4);
  EXPECT_TRUE(q2.back() == 4);
}

TEST(QueueMethods, Size) {
  s21::queue<int> q{1};
  s21::queue<int> q2{1, 2};
  s21::queue<int> q3{1, 2, 3};
  EXPECT_TRUE(q.size() == 1);
  EXPECT_TRUE(q2.size() == 2);
  EXPECT_TRUE(q3.size() == 3);
}

TEST(QueueMethods, Empty) {
  s21::queue<int> q{1};
  s21::queue<int> q2;
  EXPECT_TRUE(q.empty() == false);
  EXPECT_TRUE(q2.empty() == true);
}

TEST(QueueMethods, Assign) {
  s21::queue<int> q{1};
  s21::queue<int> q2 = q;
  EXPECT_TRUE(q.size() == 1);
  EXPECT_TRUE(q2.front() == 1);
}

TEST(QueueMethods, Front) {
  s21::queue<int> q{1, 2, 3, 4};
  EXPECT_TRUE(q.front() == 1);
  q.front() = 5;
  EXPECT_TRUE(q.front() == 5);
}

TEST(QueueMethods, Back) {
  s21::queue<int> q{1, 2, 3, 4};
  EXPECT_TRUE(q.back() == 4);
  q.back() = 5;
  EXPECT_TRUE(q.back() == 5);
}

TEST(QueueMethods, Push) {
  s21::queue<int> q{1, 2, 3, 4};
  q.push(5);
  EXPECT_TRUE(q.back() == 5);
  q.push(6);
  EXPECT_TRUE(q.back() == 6);
  q.push(7);
  EXPECT_TRUE(q.back() == 7);
}

TEST(QueueMethods, Pop) {
  s21::queue<int> q{1, 2, 3, 4};
  q.pop();
  EXPECT_TRUE(q.front() == 2);
  q.pop();
  EXPECT_TRUE(q.front() == 3);
  q.pop();
  EXPECT_TRUE(q.front() == 4);
}

TEST(QueueMethods, Swap) {
  s21::queue<int> q{1, 2, 3, 4};
  s21::queue<int> q2{5, 6};
  q.swap(q2);
  EXPECT_TRUE(q.back() == 6);
  EXPECT_TRUE(q2.back() == 4);
  EXPECT_TRUE(q.size() == 2);
  EXPECT_TRUE(q2.size() == 4);
}

TEST(QueueMethods, InsertManyBack) {
  s21::list<int> q{1, 2, 3, 4};
  s21::list<int> q2{1, 2, 3, 4, 5, 6, 7};
  q.insert_many_back(5, 6, 7);
  EXPECT_EQ(q.size(), 7);
  EXPECT_TRUE(q == q2);
}
