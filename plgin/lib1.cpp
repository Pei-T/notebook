/*
 * Copyright (C) Horizon Robotics, Inc. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#include "lib1.h"
void SharedNum::PushCommonIpcServer(std::shared_ptr<IntNum> ipc) {
  ipc_ = ipc;
  Print();
}
void SharedNum::Print() { printf("Num in Lib1: %d\n", ipc_->GetNum()); }