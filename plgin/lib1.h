/*
 * Copyright (C) Horizon Robotics, Inc. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once
#include "header.h"
class SharedNum : public ISharedNum {
 public:
  void PushCommonIpcServer(std::shared_ptr<IntNum> ipc) override;
  void Print();

 private:
  std::shared_ptr<IntNum> ipc_;
};