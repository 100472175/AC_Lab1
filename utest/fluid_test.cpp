//
// Created by cesar on 08/10/23.
//

#include "gtest/gtest.h"

TEST(String_not_equal, not_equal) {
  EXPECT_STRNE("HELLO", "WORLD");
}

TEST(Arithmetic, equal) {
  EXPECT_EQ(7 * 6, 42);
}

int main(int argc, char ** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
  return 0;
}
