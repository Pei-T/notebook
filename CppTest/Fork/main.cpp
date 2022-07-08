/*
 * Copyright (C) Horizon Robotics, Inc. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include <iostream>

#include "Fork.hpp"
int func1(int a, int b) {
  std::cout << "func1: " << a + b << std::endl;
  return 0;
}
int main() {
  Fork p(func1, 1, 2);
  func1(10, 20);
}