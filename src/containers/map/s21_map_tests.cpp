#include <gtest/gtest.h>

#include <iostream>

#include "s21_map.hpp"

TEST(Constructors, Default) {
  s21::Map<int, std::string> m;
  EXPECT_TRUE(m.size() == 0);
}

TEST(Constructors, InitList) {
  s21::Map<std::string, int> m {
        {"okay", 100},
        {"let's", 100},
        {"go", 100}
  };
  EXPECT_TRUE(m.size() == 3);
}

TEST(Constructors, Copy) {
  s21::Map<std::string, int> m {
        {"i", 100},
        {"really", 100},
        {"like", 100},
        {"corn", 100}
  };
  s21::Map<std::string, int> m2(m);
  EXPECT_TRUE(m2 == m);
}

TEST(Constructors, Move) {
  s21::Map<std::string, int> m {
        {"i", 100},
        {"really", 100},
        {"like", 100},
        {"corn", 100}
  };
  s21::Map<std::string, int> m2(std::move(m));
  EXPECT_TRUE(m2 == m);
}

TEST(Methods, Size) {
  s21::Map<int, std::string> m;
  EXPECT_TRUE(m.size() == 0);
}

TEST(Methods, Empty) {
  s21::Map<int, std::string> m;
  s21::Map<int, std::string> m2;
  EXPECT_EQ(m.empty(), true);
}

TEST(Methods, Insert) {
  s21::Map<int, std::string> m;
  //EXPECT_EQ(m.insert(), true);
}

int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);

  return RUN_ALL_TESTS();
}
