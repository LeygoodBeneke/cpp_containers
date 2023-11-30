#include "../s21_tests.h"

TEST(ListConstructors, Default) {
  s21::list<int> l;
  EXPECT_TRUE(l.size() == 0);
}

TEST(ListConstructors, Parameterized) {
  s21::list<int> l(5);
  EXPECT_TRUE(l.size() == 5);
}

TEST(ListConstructors, Copy) {
  s21::list<int> l{1, 2, 3, 4};
  s21::list<int> l2(l);
  EXPECT_EQ(l.size(), l2.size());
  EXPECT_EQ(l.front(), l2.front());
  EXPECT_EQ(l.back(), l2.back());
}

TEST(ListConstructors, Move) {
  s21::list<int> l{1, 2, 3, 4};
  s21::list<int> l2 = std::move(l);
  EXPECT_EQ(l2.size(), 4);
  EXPECT_EQ(l2.front(), 1);
  EXPECT_EQ(l2.back(), 4);
}

TEST(ListConstructors, InitList) {
  s21::list<int> l{1, 2, 3, 4};
  EXPECT_EQ(l.size(), 4);
  EXPECT_EQ(l.front(), 1);
  EXPECT_EQ(l.back(), 4);
}

TEST(ListConstructors, Range) {
  s21::list<int> l{1, 2, 3, 4};
  s21::list<int> l2(l.begin(), --l.end());
  EXPECT_EQ(l2.size(), 3);
  EXPECT_EQ(l2.front(), 1);
  EXPECT_EQ(l2.back(), 3);
}

TEST(ListOperator, Assign) {
  s21::list<int> l{1, 2, 3, 4};
  s21::list<int> l2 = l;
  s21::list<int> l3{1, 2, 3, 4};
  EXPECT_TRUE(l2 == l3);
}

TEST(ListIterator, DereferenceAndInfix) {
  s21::list<int> l{1, 2, 3, 4};
  s21::list<int>::ListIterator it = l.begin();
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  it = --l.end();
  EXPECT_EQ(*it, 4);
  EXPECT_EQ(*(--it), 3);
}

TEST(ListIterator, Postfix) {
  s21::list<int> l{1, 2, 3, 4};
  s21::list<int>::ListIterator it = l.begin();
  s21::list<int>::ListIterator it2 = it++;
  EXPECT_EQ(*it, 2);
  EXPECT_EQ(*it2, 1);
  it = --l.end();
  it2 = it--;
  EXPECT_EQ(*it, 3);
  EXPECT_EQ(*it2, 4);
}

TEST(ListIterator, Eq) {
  s21::list<int> l{1, 2, 3, 4};
  s21::list<int>::ListIterator it = l.begin();
  s21::list<int>::ListIterator it2 = l.begin();
  EXPECT_TRUE(it == it2);
}

TEST(ListIterator, NonEq) {
  s21::list<int> l{1, 2, 3, 4};
  s21::list<int>::ListIterator it = l.begin();
  s21::list<int>::ListIterator it2 = ++l.begin();
  EXPECT_TRUE(it != it2);
}

TEST(ListIterator, AddAssign) {
  s21::list<int> l{1, 2, 3, 4, 5, 6};
  s21::list<int>::ListIterator it = l.begin();
  it += 2;
  EXPECT_EQ(*it, 3);
  it += 3;
  EXPECT_EQ(*it, 6);
}

TEST(ListIterator, SubAssign) {
  s21::list<int> l{1, 2, 3, 4};
  s21::list<int>::ListIterator it = l.begin();
  it += 2;
  EXPECT_EQ(*it, 3);
}

TEST(ListConstIterator, Dereference) {
  s21::list<int> l{1, 2, 3, 4};
  s21::list<int>::ListConstIterator it = l.begin();
  EXPECT_EQ(*it, 1);
}

TEST(ListConstIterator, Infix) {
  s21::list<int> l{1, 2, 3, 4};
  s21::list<int>::ListConstIterator it = ++l.begin();
  EXPECT_EQ(*it, 2);
  s21::list<int>::ListConstIterator it2 = --it;
  EXPECT_EQ(*it2, 1);
}

TEST(ListConstIterator, Postfix) {
  s21::list<int> l{1, 2, 3, 4};
  s21::list<int>::ListConstIterator it = l.begin();
  EXPECT_EQ(*it, 1);
  s21::list<int>::ListConstIterator it2 = it++;
  EXPECT_EQ(*it2, 1);
  EXPECT_EQ(*it, 2);
  it--;
  EXPECT_EQ(*it, 1);
}

TEST(ListConstIterator, Eq) {
  s21::list<int> l{1, 2, 3, 4};
  s21::list<int>::ListConstIterator it = l.begin();
  s21::list<int>::ListConstIterator it2 = l.begin();
  EXPECT_TRUE(it == it2);
}

TEST(ListConstIterator, NonEq) {
  s21::list<int> l{1, 2, 3, 4};
  s21::list<int>::ListConstIterator it = l.begin();
  s21::list<int>::ListConstIterator it2 = l.end();
  EXPECT_TRUE(it != it2);
}

TEST(ListMethods, Clear) {
  s21::list<int> l(5);
  l.clear();
  EXPECT_EQ(l.size(), 0);
}

TEST(ListMethods, Size) {
  s21::list<int> l(5);
  EXPECT_EQ(l.size(), 5);
}

TEST(ListMethods, MaxSize) {
  s21::list<int> l(5);
  s21::list<int> l2(5);
  EXPECT_EQ(l.max_size(), l2.max_size());
}

TEST(ListMethods, Empty) {
  s21::list<int> l(5);
  s21::list<int> l2;
  s21::list<int> l3(5);
  l3.clear();
  EXPECT_EQ(l.empty(), false);
  EXPECT_EQ(l2.empty(), true);
  EXPECT_EQ(l2.empty(), true);
}

TEST(ListMethods, Begin) {
  s21::list<int> l{1, 2, 3};
  EXPECT_EQ(*(++l.begin()), 2);
}

TEST(ListMethods, End) {
  s21::list<int> l{1, 2, 3};
  EXPECT_EQ(*(--l.end()), 3);
}

TEST(ListMethods, Front) {
  s21::list<int> l{1, 2, 3};
  EXPECT_EQ(l.front(), 1);
  l.push_front(2);
  EXPECT_EQ(l.front(), 2);
}

TEST(ListMethods, Back) {
  s21::list<int> l{1, 2, 3, 4};
  EXPECT_EQ(l.back(), 4);
  l.push_back(7);
  EXPECT_EQ(l.back(), 7);
}

TEST(ListMethods, PushBack) {
  s21::list<int> l;
  l.push_back(1);
  EXPECT_EQ(l.back(), 1);
  l.push_back(2);
  EXPECT_EQ(l.back(), 2);
  l.push_back(3);
  EXPECT_EQ(l.back(), 3);
  EXPECT_EQ(l.size(), 3);
}

TEST(ListMethods, PopBack) {
  s21::list<int> l{1, 2, 3};
  l.pop_back();
  EXPECT_EQ(l.back(), 2);
  l.pop_back();
  EXPECT_EQ(l.back(), 1);
  EXPECT_EQ(l.size(), 1);
}

TEST(ListMethods, PushFront) {
  s21::list<int> l{1, 2, 3};
  l.push_front(9);
  EXPECT_EQ(l.front(), 9);
  l.push_front(8);
  EXPECT_EQ(l.front(), 8);
  EXPECT_EQ(l.size(), 5);
}

TEST(ListMethods, PopFront) {
  s21::list<int> l{1, 2, 3};
  l.pop_front();
  EXPECT_EQ(l.front(), 2);
  l.pop_front();
  EXPECT_EQ(l.front(), 3);
  EXPECT_EQ(l.size(), 1);
}

TEST(ListMethods, Insert) {
  s21::list<int> l{1, 2, 3, 4};
  l.insert(l.begin(), 5);
  EXPECT_EQ(l.front(), 5);
  l.insert(l.begin(), 6);
  EXPECT_EQ(l.front(), 6);
  l.insert(l.end(), 8);
  EXPECT_EQ(l.back(), 8);
}

TEST(ListMethods, InsertCount) {
  s21::list<int> l{1, 2, 3, 4};
  l.insert(l.end(), 2, 0);
  EXPECT_EQ(l.back(), 0);
  l.insert(l.begin(), 3, 5);
  EXPECT_EQ(l.front(), 5);
  EXPECT_EQ(l.size(), 9);
}

TEST(ListMethods, InsertMany) {
  s21::list<int> l{1, 2, 3, 4};
  s21::list<int> l2{5, 6, 7, 1, 2, 3, 4};
  l.insert_many(l.begin(), 5, 6, 7);
  EXPECT_EQ(l.size(), 7);
  EXPECT_TRUE(l == l2);
}

TEST(ListMethods, InsertManyBack) {
  s21::list<int> l{1, 2, 3, 4};
  s21::list<int> l2{1, 2, 3, 4, 5, 6, 7};
  l.insert_many_back(5, 6, 7);
  EXPECT_EQ(l.size(), 7);
  EXPECT_TRUE(l == l2);
}

TEST(ListMethods, InsertManyFront) {
  s21::list<int> l{1, 2, 3, 4};
  s21::list<int> l2{5, 6, 7, 1, 2, 3, 4};
  l.insert_many_front(5, 6, 7);
  EXPECT_EQ(l.size(), 7);
  EXPECT_TRUE(l == l2);
}

TEST(ListMethods, Erase) {
  s21::list<int> l{1, 2, 3, 4, 5};
  l.erase(l.begin());
  EXPECT_EQ(l.front(), 2);
  l.erase(l.begin());
  EXPECT_EQ(l.front(), 3);
  l.erase(--l.end());
  EXPECT_EQ(*(--l.end()), 4);
}

TEST(ListMethods, EraseThrow) {
  s21::list<int> l{1, 2, 3, 4};
  try {
    l.erase(l.end());
    FAIL();
  } catch (std::out_of_range& t) {
    EXPECT_EQ(t.what(), std::string("Cannot erase the end iterator"));
  }
}

TEST(ListMethods, Swap) {
  s21::list<int> l{1, 2, 3, 4};
  s21::list<int> l2{5, 6, 7, 8};
  l.swap(l2);
  EXPECT_EQ(l.front(), 5);
  EXPECT_EQ(l2.front(), 1);
  EXPECT_EQ(l.back(), 8);
  EXPECT_EQ(l2.back(), 4);
}

TEST(ListMethods, Reverse) {
  s21::list<int> l{1, 2, 3, 4};
  l.reverse();
  EXPECT_EQ(l.front(), 4);
  EXPECT_EQ(*(++l.begin()), 3);
  EXPECT_EQ(l.back(), 1);
}

TEST(ListMethods, Splice) {
  s21::list<int> l{1, 2, 3, 4};
  s21::list<int> l2{4, 5, 6};
  l.splice(l.begin(), l2);
  EXPECT_EQ(l.front(), 4);
  EXPECT_EQ(*(++l.begin()), 5);
  EXPECT_EQ(l.back(), 4);
  EXPECT_EQ(l.size(), 7);
}

TEST(ListMethods, Sort) {
  s21::list<int> l{4, 3, 2, 1};
  s21::list<int> l2{1, 2, 3, 4};
  l.sort();
  EXPECT_TRUE(l == l2);
}

TEST(ListMethods, Merge) {
  s21::list<int> l{1, 2, 3, 4};
  s21::list<int> l2{5, 6, 7, 8};
  s21::list<int> l3{1, 2, 3, 4, 5, 6, 7, 8};
  l.merge(l2);
  EXPECT_TRUE(l == l3);
}

TEST(ListMethods, Unique) {
  s21::list<int> l{1, 2, 2, 3, 3, 3, 4, 5, 5, 6};
  s21::list<int> l2{1, 2, 3, 4, 5, 6};
  l.unique();
  EXPECT_TRUE(l == l2);
}
