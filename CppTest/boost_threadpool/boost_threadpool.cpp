/*
 * Copyright (C) Horizon Robotics, Inc. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

// #include <boost/asio.hpp>
#include <boost/asio/post.hpp>
#include <boost/asio/thread_pool.hpp>
#include <iostream>
#include <thread>
void Task1() {
  std::cout << "Task 1 Start\n";
  for (uint32_t i = 0; i < 10; i++) {
    std::cout << "Task 1:" << i << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
}

class Task2 {
  public:
  void operator()() {
    std::cout << "\t\tTask 2 Start\n";
    for (uint32_t i = 0; i < 20; i++) {
      std::cout << "\t\tTask 2:" << i << "\n";
      std::this_thread::sleep_for(std::chrono::milliseconds(500));
    }
  }
};

int main() {
  Task2 task2;
  boost::asio::thread_pool pool(2);
  boost::asio::post(pool, Task1);
  std::this_thread::sleep_for(std::chrono::milliseconds(200));
  boost::asio::post(pool,task2);
  pool.join();
}