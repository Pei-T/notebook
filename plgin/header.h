/*
 * Copyright (C) Horizon Robotics, Inc. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */
#pragma once
#include <memory>
class IntNum {
 public:
  virtual int GetNum() = 0;
  virtual void SetNum(int a) = 0;
};
class ISharedNum {
 public:
  virtual void PushCommonIpcServer(std::shared_ptr<IntNum> ipc) = 0;
};