#pragma once
#include <iostream>
namespace fsm {
enum StateOp { kRequest = 0, kComfirm, kReject };
struct Message {
  char topic[32];
  char src_name[32];
  char des_name[32];
  uint16_t single;
  uint16_t state_op;
  char extra_data[32];
};
}  // namespace fsm
