/*
 * Copyright (C) Horizon Robotics, Inc. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include <gtest/gtest.h>

#include <iostream>
#include <string>

#include "header.h"

int Func1(int a, int b) { return a + b; }

int Func2(int a, int b) { return a - b; }

// TEST(AddTest, Normal) {
//   auto tmp = Func1(3, 4);
//   EXPECT_EQ(tmp, 7);
// }

int main() {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}