#pragma once

#include <unistd.h>

#include <condition_variable>
#include <functional>
#include <future>
#include <iostream>
#include <map>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

class Timer {
 public:
  Timer() {
    run_flag_.store(true);
    th_ = std::thread(std::bind(&Timer::BackFunc_, this));
  }

  ~Timer() {
    run_flag_.store(false);
    funcs_[now_()] = std::make_shared<std::function<void()>>([]() {});
    cv_.notify_all();
    th_.join();
  }

  void InsertFunc(uint32_t time, std::function<void()> f) {
    auto sp_f = std::make_shared<std::function<void()>>(f);
    funcs_[now_() + std::chrono::milliseconds(time)] = sp_f;
    std::unique_lock<std::mutex> lck(mtx_);
    cv_.notify_all();
  }

  void InsertFunc(uint32_t time, std::shared_ptr<std::function<void()>> f) {
    funcs_[now_() + std::chrono::milliseconds(time)] = f;
    std::unique_lock<std::mutex> lck(mtx_);
    cv_.notify_all();
  }

 private:
  std::thread th_;
  std::mutex mtx_;
  std::condition_variable cv_;
  std::atomic<bool> run_flag_;
  using time_point = std::chrono::_V2::steady_clock::time_point;
  std::map<time_point, std::shared_ptr<std::function<void()>>> funcs_;
  inline std::chrono::_V2::steady_clock::time_point now_() {
    return std::chrono::steady_clock::now();
  }
  void BackFunc_() {
    while (run_flag_.load()) {
      std::unique_lock<std::mutex> lck(mtx_);
      cv_.wait(lck, [=]() -> bool { return funcs_.size() != 0; });
      lck.unlock();
      std::this_thread::sleep_until(funcs_.begin()->first);
      if (*(funcs_.begin()->second) != nullptr) (*(funcs_.begin()->second))();
      funcs_.erase(funcs_.begin());
    }
  }
};

template <class T>
class Node {
 public:
  enum State { UNKNOWN, HIGH, LOW };
  Node() {}
  Node(Timer* tw, T high_val, uint32_t high_times, uint32_t high_time,
       T low_val, uint32_t low_times, uint32_t low_time,
       State default_state = State::LOW) {
    tw_ = tw;
    HighVal = high_val;
    HighCount = high_times;
    HighTimeout = high_time;
    LowVal = low_val;
    LowCount = low_times;
    LowTimeout = low_time;
    LastState = new (State);
    *LastState = default_state;
    tmp_state_ = default_state;
    LowCbSwither = std::make_shared<std::function<void()>>();
    HighCbSwither = std::make_shared<std::function<void()>>();
  }
  void SetHighCb(std::function<void()> f) {
    HighCb = std::bind(
        [](std::function<void()> f, Node::State* p) {
          f();
          *p = Node::State::HIGH;
        },
        f, LastState);
  }
  void SetLowCb(std::function<void()> f) {
    LowCb = std::bind(
        [](std::function<void()> f, Node::State* p) {
          f();
          *p = Node::State::LOW;
        },
        f, LastState);
  }
  void CheckValue(T val) {
    if (val < HighVal && *LastState != HIGH && tmp_state_ != HIGH) {
      LastVal = val;
      return;
    }

    if (LastVal < HighVal && val >= HighVal && *LastState != State::HIGH) {
      tmp_state_ = Node::State::HIGH;
      // printf("CASE1\n");
    } else if (LastVal >= LowVal && val < LowVal && *LastState != State::LOW) {
      tmp_state_ = Node::State::LOW;
      // printf("CASE2\n");
    } else if (tmp_state_ == Node::State::HIGH && val < HighVal) {
      tmp_state_ = Node::State::UNKNOWN;
      // printf("CASE3\n");
    } else if (tmp_state_ == Node::State::LOW && val > LowVal) {
      tmp_state_ = Node::State::UNKNOWN;
      // printf("CASE4\n");
    }

    if (tmp_state_ == Node::State::HIGH) {
      HighHock();
      // printf("CASE5\n");
    } else if (tmp_state_ == Node::State::LOW) {
      LowHock();
      // printf("CASE6\n");
    } else {
      ClearHock();
      // printf("CASE7\n");
    }
    LastVal = val;
  }

 private:
  Timer* tw_;
  State* LastState;
  State tmp_state_;
  T LowVal, HighVal, LastVal;
  uint32_t LowCount, HighCount, TmpLowCount, TmpHighCount;
  uint32_t HighTimeout, LowTimeout;
  std::function<void()> LowCb, HighCb;
  std::shared_ptr<std::function<void()>> LowCbSwither, HighCbSwither;

  void HighHock() {
    TmpHighCount++;
    TmpLowCount = 0;
    *LowCbSwither = (std::function<void()>());
    if (TmpHighCount == HighCount && *LastState != HIGH) {
      *HighCbSwither = HighCb;
      tw_->InsertFunc(HighTimeout, HighCbSwither);
      // printf("Set high\n");
    }
  }
  void LowHock() {
    TmpHighCount = 0;
    TmpLowCount++;
    *HighCbSwither = (std::function<void()>());
    if (TmpLowCount == LowCount && *LastState != LOW) {
      *LowCbSwither = LowCb;
      tw_->InsertFunc(LowTimeout, LowCbSwither);
      // printf("Set low\n");
    }
  }
  void ClearHock() {
    TmpHighCount = 0;
    TmpLowCount = 0;
    *HighCbSwither = (std::function<void()>());
    *LowCbSwither = (std::function<void()>());
    // printf("Clear all\n");
  }
};

template <class P>
class DebounceServer {
 public:
  DebounceServer(){};

  void Insert(std::string name, P HighValue, std::function<void()> high_f,
              std::function<void()> low_f) {
    Node<P> tmp(&tw, HighValue, 1, 1000, HighValue, 1, 1000);
    tmp.SetHighCb(high_f);
    tmp.SetLowCb(low_f);
    nodes_.insert(std::make_pair(name, tmp));
  }
  void Insert(std::string name, P Highvalue, uint32_t high_times,
              uint32_t high_time, std::function<void()> high_f, P low_val,
              uint32_t low_times, uint32_t low_time,
              std::function<void()> low_f) {
    Node<P> tmp(&tw, Highvalue, high_times, high_time, low_val, low_times,
                low_time);
    tmp.SetHighCb(high_f);
    tmp.SetLowCb(low_f);
    nodes_.insert(std::make_pair(name, tmp));
  }
  void InsertBool(std::string name, uint32_t high_times, uint32_t high_time,
                  std::function<void()> high_f, uint32_t low_times,
                  uint32_t low_time, std::function<void()> low_f) {
    Node<P> tmp(&tw, (P)1, high_times, high_time, (P)0, low_times, low_time);
    tmp.SetHighCb(high_f);
    tmp.SetLowCb(low_f);
    nodes_.insert(std::make_pair(name, tmp));
  }
  void CheckVal(std::string name, P val) { nodes_[name].CheckValue(val); }
  void SetHighCb(std::string name, std::function<void()> high_f) {
    auto it = nodes_.find(name);
    if (it != nodes_.end()) {
      it->second.SetHighCb(high_f);
    }
  }
  void SetLowCb(std::string name, std::function<void()> high_f) {
    auto it = nodes_.find(name);
    if (it != nodes_.end()) {
      it->second.SetLowCb(high_f);
    }
  }

 private:
  Timer tw;
  std::map<std::string, Node<P>> nodes_;
};