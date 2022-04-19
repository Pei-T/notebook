#pragma once

#include <functional>
#include <queue>
#include <string>
#include <unordered_map>

#include "res.hpp"
namespace fsm {
class MessageDistribution {
 public:
  MessageDistribution() {}
  void Register(std::string name, std::function<void(std::string)> f) {
    func_map_[name] = f;
  }
  Res PushMsg(std::string msg) {
    std::string idx = msg.substr(0, 32);
    auto i = func_map_.find(msg);
    if (i != func_map_.end()) {
      (i->second)(msg);
      return Res::kOK();
    } else {
      return Res::kError("Topic :[" + idx + "] has not set function.");
    }
  }

 private:
  std::unordered_map<std::string, std::function<void(std::string)>> func_map_;
};
}  // namespace fsm
