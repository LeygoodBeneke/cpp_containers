#include <iostream>
#include "s21_list.h"

#include <gtest/gtest.h>

TEST(Constructors, Default) {
  s21::list<int> l;
  ASSERT_TRUE( == 5);
}
