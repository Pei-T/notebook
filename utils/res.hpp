#pragma once
#include <string>
class Res {
 private:
  enum State { kOk = 0, kError };

 public:
  Res() : sta_(State::kOk) {}
  Res(State sta, std::string Msg) : sta_(sta) {
    printf("Error:%s\n", Msg.c_str());
  }

  static Res OK() { return Res(); }
  static Res Error(std::string err_msg) {return Res(State::kError, err_msg); }

  bool IsOk() { return sta_ == State::kOk; }
  bool IsErr() { return sta_ == State::kError; }
  bool operator==(const Res& other) { return sta_ == other.sta_; }

 private:
  State sta_;
};
