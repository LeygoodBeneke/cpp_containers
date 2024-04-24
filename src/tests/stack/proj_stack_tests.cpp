#include "../s21_tests.hpp"

TEST(StackConstructors, Default) {
  s21::stack<int> s;
  EXPECT_TRUE(s.size() == 0);
}

TEST(StackConstructors, InitList) {
  s21::stack<int> s{1, 2, 3, 4};
  EXPECT_TRUE(s.size() == 4);
  EXPECT_TRUE(s.top() == 4);
}

TEST(StackConstructors, Copy) {
  s21::stack<int> s{1, 2, 3, 4};
  s21::stack<int> s2(s);
  EXPECT_TRUE(s == s2);
  EXPECT_TRUE(s.top() == s2.top());
}

TEST(StackConstructors, Move) {
  s21::stack<int> s{1, 2, 3, 4};
  s21::stack<int> s2(std::move(s));
  EXPECT_TRUE(s2.size() == 4);
  EXPECT_TRUE(s2.top() == 4);
}

TEST(StackMethods, Size) {
  s21::stack<int> s{1};
  s21::stack<int> s2{1, 2};
  s21::stack<int> s3{1, 2, 3};
  EXPECT_TRUE(s.size() == 1);
  EXPECT_TRUE(s2.size() == 2);
  EXPECT_TRUE(s3.size() == 3);
}

TEST(StackMethods, Empty) {
  s21::stack<int> s{1};
  s21::stack<int> s2;
  EXPECT_TRUE(s.empty() == false);
  EXPECT_TRUE(s2.empty() == true);
}

TEST(StackMethods, Assign) {
  s21::stack<int> s{1};
  s21::stack<int> s2 = s;
  EXPECT_TRUE(s.size() == 1);
  EXPECT_TRUE(s2.top() == 1);
}

TEST(StackMethods, Top) {
  s21::stack<int> s{1, 2, 3, 4};
  EXPECT_TRUE(s.top() == 4);
  s.top() = 5;
  EXPECT_TRUE(s.top() == 5);
}

TEST(StackMethods, Push) {
  s21::stack<int> s{1, 2, 3, 4};
  s.push(5);
  EXPECT_TRUE(s.top() == 5);
  s.push(6);
  EXPECT_TRUE(s.top() == 6);
  s.push(7);
  EXPECT_TRUE(s.top() == 7);
}

TEST(StackMethods, Pop) {
  s21::stack<int> s{1, 2, 3, 4};
  s.pop();
  EXPECT_TRUE(s.top() == 3);
  s.pop();
  EXPECT_TRUE(s.top() == 2);
  s.pop();
  EXPECT_TRUE(s.top() == 1);
}

TEST(StackMethods, Swap) {
  s21::stack<int> s{1, 2, 3, 4};
  s21::stack<int> s2{5, 6};
  s.swap(s2);
  EXPECT_TRUE(s.top() == 6);
  EXPECT_TRUE(s2.top() == 4);
  EXPECT_TRUE(s.size() == 2);
  EXPECT_TRUE(s2.size() == 4);
}

TEST(StackMethods, InsertManyFront) {
  s21::list<int> s{1, 2, 3, 4};
  s21::list<int> s2{5, 6, 7, 1, 2, 3, 4};
  s.insert_many_front(5, 6, 7);
  EXPECT_EQ(s.size(), 7);
  EXPECT_TRUE(s == s2);
}
