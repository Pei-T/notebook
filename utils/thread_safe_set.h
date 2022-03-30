/*
 * Copyright (C) Horizon Robotics, Inc. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */
#include <condition_variable>
#include <mutex>
#include <set>

template <class T>
class ThreadSafeSet {
 public:
  ThreadSafeSet() {}
  ~ThreadSafeSet() {}
  void Insert(T data) {
    std::lock_guard<std::mutex> lck(mtx_);
    data_.insert(data);
  }
  bool Erase(T data) {
    std::lock_guard<std::mutex> lck(mtx_);
    auto it = data_.find(data);
    if (it == data_.end()) {
      return false;
    }
    data_.erase(it);
    if (data_.size() == 0) {
      cv_.notify_one();
    }
    return true;
  }
  uint32_t Size() {
    std::lock_guard<std::mutex> lck(mtx_);
    return data_.size();
  }
  void Clear() {
    std::lock_guard<std::mutex> lck(mtx_);
    data_.clear();
    cv_.notify_one();
  }
  std::set<T> GetCopy() {
    std::lock_guard<std::mutex> lck(mtx_);
    std::set<T> res = data_;
    return res;
  }
  bool WaitForZeroSize(uint32_t timeout_ms) {
    std::unique_lock<std::mutex> lck(mtx_);
    return cv_.wait_for(lck, std::chrono::milliseconds(timeout_ms),
                        [&]() { return data_.size() == 0; });
  }

 private:
  std::mutex mtx_;
  std::condition_variable cv_;
  std::set<T> data_;
};