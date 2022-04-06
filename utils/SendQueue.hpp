#pragma once
#include <unistd.h>

#include <condition_variable>
#include <functional>
#include <future>
#include <iostream>
#include <mutex>
#include <queue>
#include <string>
#include <thread>

class SendQueue {
 public:
  SendQueue() {
    send_f_ = [](std::string) { return 0; };
    th_ = std::thread(&SendQueue::ThreadFunc_, this);
  }
  ~SendQueue() {
    break_all_wait_ = true;
    std::unique_lock<std::mutex> lock(mutex_);
    cv_.notify_all();
    lock.unlock();
    th_.join();
  }

  void SetSendFunc(std::function<int(std::string)> f) { send_f_ = f; }

  std::future<int> PushToSend(char* p, uint32_t len) {
    auto tmp_sp = std::make_shared<std::packaged_task<int()>>(
        std::bind(send_f_, std::string(p, len)));
    auto res = (*tmp_sp).get_future();
    std::lock_guard<std::mutex> lock(mutex_);
    data_.emplace(tmp_sp);
    cv_.notify_all();
    return res;
  }

  std::future<int> PushToSend(std::string data) {
    auto tmp_sp = std::make_shared<std::packaged_task<int()>>(
        std::bind(send_f_, std::string(data)));
    auto res = (*tmp_sp).get_future();
    std::lock_guard<std::mutex> lock(mutex_);
    data_.emplace(tmp_sp);
    cv_.notify_all();
    return res;
  }

 private:
  volatile bool break_all_wait_ = false;
  std::mutex mutex_;
  std::thread th_;
  std::condition_variable cv_;
  std::queue<std::shared_ptr<std::packaged_task<int()>>> data_;
  std::function<int(std::string)> send_f_;

 public:
  void ThreadFunc_() {
    std::packaged_task<int()> tmp_pt_;
    while (!break_all_wait_) {
      std::unique_lock<std::mutex> lock(mutex_);
      cv_.wait(lock, [this]() { return break_all_wait_ || !data_.empty(); });
      if (break_all_wait_) break;
      (*data_.front())();
      data_.pop();
    }
    std::cout << "ThreadFunc_ quit" << std::endl;
  }
};