/*
 * Copyright (C) Horizon Robotics, Inc. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "header.h"

class IntNumImpl : public IntNum {
 public:
  int GetNum() override{ return num_; }
  void SetNum(int a) override{ num_ = a; }

 private:
  int num_{0};
};