/*
 * Copyright (C) Horizon Robotics, Inc. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */
#include "libone.h"

#include <iostream>
#include <thread>
int Hello() {
  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  printf("HelloWorld\n");

  return 0;
}