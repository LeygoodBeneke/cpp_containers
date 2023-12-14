#include <gtest/gtest.h>

#include <iostream>
#include <string>

#include "s21_map.hpp"

TEST(Constructors, Default) {
  s21::map<std::string, int> m;
  EXPECT_TRUE(m.size() == 0);
}

TEST(Constructors, InitList) {
  s21::map<std::string, int> m {
        {"okay", 100},
        {"let's", 200},
        {"go", 300}
  };
  EXPECT_TRUE(m.size() == 3);
}

TEST(Constructors, Copy) {
  s21::map<std::string, int> m {
        {"okay", 100},
        {"let's", 200},
        {"go", 300}
  };
  s21::map<std::string, int> m2(m);
  EXPECT_TRUE(m2 == m);
}

TEST(Constructors, Move) {
  s21::map<std::string, int> m {
        {"okay", 100},
        {"let's", 200},
        {"go", 300}
  };
  s21::map<std::string, int> m2 {
        {"okay", 100},
        {"let's", 200},
        {"go", 300}
  };
  s21::map<std::string, int> m3(std::move(m));
  EXPECT_TRUE(m3 == m2);
}

// TEST(Operator, Assign) {
//   s21::map<std::string, int> m {
//         {"okay", 100},
//         {"let's", 200},
//         {"go", 300}
//   };
//   s21::map<std::string, int> m2 = m;
//   EXPECT_TRUE(m2 == m);
// }

TEST(Methods, Size) {
  s21::map<std::string, int> m;
  s21::map<std::string, int> m2 {
        {"okay", 100},
        {"let's", 200},
        {"go", 300}
  };
  EXPECT_EQ(m.size(), 0);
  EXPECT_EQ(m2.size(), 3);
}

TEST(Methods, Empty) {
  s21::map<std::string, int> m;
  s21::map<std::string, int> m2 {
        {"okay", 100},
        {"let's", 200},
        {"go", 300}
  };
  EXPECT_EQ(m.empty(), true);
  EXPECT_EQ(m2.empty(), false);
}

// TEST(Methods, InsertKeyValue) {
//   s21::map<std::string, int> m;
//   bool status = m.insert("okay", 100).second;
//   EXPECT_EQ(status, true);
//   EXPECT_EQ(m.at("okay"), 100);
// }

// TEST(Methods, InsertPair) {
//   s21::map<std::string, int> m;
//   bool status = m.insert(std::make_pair("okay", 100)).second;
//   EXPECT_EQ(status, true);
//   EXPECT_EQ(m.at("okay"), 100);
// }

// TEST(Methods, InsertOrAssign) {
//   s21::map<std::string, int> m {
//         {"okay", 100},
//         {"let's", 200},
//         {"go", 300}
//   };
//   bool status = m.insert_or_assign("okay", 100).second;
//   EXPECT_EQ(status, false);
//   status = m.insert_or_assign("okay", 400).second;
//   EXPECT_EQ(status, true);
// }

// TEST(Methods, AtThrow) {
//   s21::map<std::string, int> m {
//         {"okay", 100},
//         {"let's", 200},
//         {"go", 300}
//   };
//   EXPECT_THROW(m.at("corn"), std::out_of_range);
// }

// TEST(Operator, Index) {
//   s21::map<std::string, int> m {
//         {"okay", 100},
//         {"let's", 200},
//         {"go", 300}
//   };
//   EXPECT_EQ(m["okay"], 100);
//   EXPECT_EQ(m["go"], 300);
// }

// TEST(Methods, Begin) {
//   s21::map<std::string, int> m {
//         {"okay", 100},
//         {"let's", 200},
//         {"go", 300}
//   };
//   EXPECT_EQ(*m.begin().first, "okay");
//   EXPECT_EQ(*m.begin().second, 100);
//   EXPECT_EQ(*(++m.begin()).first, "let's");
//   EXPECT_EQ(*(++m.begin()).second, 200);
// }+
// TEST(Methods, End) --{
//   s21::map<std::string, int> m {
//         {"okay", 100},
//         {"let's", 200},
//         {"go", 300}
//   };
//   EXPECT_EQ(*(--m.end()).first, "go");
//   EXPECT_EQ(*(--m.end()).second, 300);
// }

// TEST(Methods, Clear) {
//   s21::map<std::string, int> m {
//         {"okay", 100},
//         {"let's", 200},
//         {"go", 300}
//   };
//   m.clear();
//   EXPECT_EQ(m.empty, true);
// }

// TEST(Methods, Erase) {
//   s21::map<std::string, int> m {
//         {"okay", 100},
//         {"let's", 200},
//         {"go", 300}
//   };
//   m.erase(m.begin());
// EXPECT_EQ(m.size(), 2);
// EXPECT_EQ(*m.begin().first, "let's");
// }

// TEST(Methods, Swap) {
//   s21::map<std::string, int> m {
//         {"okay", 100},
//         {"let's", 200},
//         {"go", 300}
//   };
//   s21::map<std::string, int> m2 {
//         {"meme", 500}
//   };
//   m.swap(m2);
//   EXPECT_EQ(m.size(), 1);
//   EXPECT_EQ(m2.size(), 3);
//   EXPECT_EQ(*m.begin().second, 500);
//   EXPECT_EQ(*m2.begin().second, 100);
// }

// TEST(Methods, Swap) {
//   s21::map<std::string, int> m {
//         {"okay", 100},
//         {"let's", 200},
//         {"go", 300}
//   };
//   s21::map<std::string, int> m2 {
//         {"meme", 500}
//   };
//   m.swap(m2);
//   EXPECT_EQ(m.size(), 1);
//   EXPECT_EQ(m2.size(), 3);
//   EXPECT_EQ(*m.begin().second, 500);
//   EXPECT_EQ(*m2.begin().second, 100);
// }

// TEST(Methods, Merge) {
//   s21::map<std::string, int> m {
//         {"okay", 100},
//         {"let's", 200},
//         {"go", 300}
//   };
//   s21::map<std::string, int> m2 {
//         {"meme", 500}
//   };
//   m.merge(m2);
//   EXPECT_EQ(m.size(), 4);
//   EXPECT_EQ(m["okay"], 100);
//   EXPECT_EQ(m["meme"], 500);
// }

// TEST(Methods, Contains) {
//   s21::map<std::string, int> m {
//         {"okay", 100},
//         {"let's", 200},
//         {"go", 300}
//   };
//   EXPECT_EQ(m.contains("okay"), true);
//   EXPECT_EQ(m.contains("meme"), false);
// }

// int main(int argc, char** argv) {
//   ::testing::InitGoogleTest(&argc, argv);

//   return RUN_ALL_TESTS();
// }
