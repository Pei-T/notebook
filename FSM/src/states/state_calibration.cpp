/*
 * Copyright (C) Horizon Robotics, Inc. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */
#include "states.h"
namespace fm {
class Calibration : public State {
 public:
  Calibration() : State("Calibration"){};
  int OnEntry() { return 0; }
  int OnExit() { return 0; };
  int CheckCondition() { return 0; };
  int HandleMessage(void* data) { return 0; };
  int Info() {
    LOG_INFO("This is Calibration State.\n");
    return 0;
  }
};
REGISTER(Calibration);
}  // namespace fm