/******************************************************************************
 * Copyright 2021 The Horozon Robotics. All Rights Reserved.
 *
 * this file has a binary dependency on apollo
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *****************************************************************************/
#pragma once

#include <condition_variable>
#include <mutex>
#include <list>
#include <thread>
#include <utility>


template <typename T>
class ThreadSafeList {
 public:
  ThreadSafeList() {}

  ~ThreadSafeList() {}

  void Enqueue(const T& element) {
    std::lock_guard<std::mutex> lock(mutex_);
    list_.emplace(element);
  }

  bool Dequeue(T* element) {
    std::lock_guard<std::mutex> lock(mutex_);
    if (list_.empty()) {
      return false;
    }
    *element = std::move(list_.front());
    list_.pop();
    return true;
  }

  typename std::list<T>::size_type Size() {
    std::lock_guard<std::mutex> lock(mutex_);
    return list_.size();
  }

  bool Empty() {
    std::lock_guard<std::mutex> lock(mutex_);
    return list_.empty();
  }

  void EraseNode(typename std::list<T>::iterator ite) {
    std::lock_guard<std::mutex> lock(mutex_);
    list_.erase(ite);
  }

  template <typename symbol>
  typename std::list<T>::iterator Find(const symbol& to_be_found) {
    std::lock_guard<std::mutex> lock(mutex_);
    typename std::list<T>::iterator it;
    FIND_WITH_ITERATOR(list_, it, (*it == to_be_found));
    return it;
  }

  typename std::list<T>::iterator End() {
    std::lock_guard<std::mutex> lock(mutex_);
    return list_.end();
  }

 private:
  std::mutex mutex_;
  std::list<T> list_;

  DISALLOW_COPY_AND_ASSIGN(ThreadSafeList);
};
