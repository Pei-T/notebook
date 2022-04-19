
/*
 * Copyright (C) Horizon Robotics, Inc. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */
#pragma once
#include <stdint.h>

#include <atomic>
#include <iostream>

namespace interface {
enum RetType {
  kSuccess = 0,
  kNoIpcComponent = 1,
  kFactoryHasNoProduct = 2,
  kWrongIoDirection = 3,
  kApiNotSupported = 4,
  kTimeout = 5,
  kNoSessionComponent = 6,
  kFail = 7
};

class IpcInterface {
 public:
  IpcInterface() {}
  virtual ~IpcInterface() {}
  RetType Send(const void* data, uint32_t l, bool is_block = false) {
    if (is_block) {
      return DoBlockSend(data, l);
    } else {
      return DoNonBlockSend(data, l);
    }
  }
  RetType Recv(const void* data, uint32_t* l, int32_t time_ms = -1) {
    if (time_ms == -1) {
      return DoBlockRecv(data, l);
    } else {
      return DoNonBlockRecv(data, l, time_ms);
    }
  }
  virtual RetType SetSubscribTopic(const std::string& topic) = 0;

 protected:
  virtual RetType DoBlockSend(const void* data, uint32_t l) = 0;
  virtual RetType DoNonBlockSend(const void* data, uint32_t l) = 0;
  virtual RetType DoBlockRecv(const void* data, uint32_t* l) = 0;
  virtual RetType DoNonBlockRecv(const void* data, uint32_t* l, int32_t t) = 0;
};

}  // namespace interface
