/*
 * Copyright (C) Horizon Robotics, Inc. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

#pragma once
#include <assert.h>
#include <unistd.h>

#include <functional>
class Fork {
 public:
  Fork() {}
  template <class F, class... A>
  Fork(F&& f, A&&... args) {
    pid_ = fork();
    if (pid_ < 0) {
      printf("fork() create child process failure.\n");
    } else if (pid_ == 0) {
      printf("\n\nChild process.Call f(args...).\n", pid_);
      assert(typeid(int) == typeid(f(args...)));
      int res = f(args...);
      quick_exit(res);
    } else {
      printf("Parent process has creat a child process pid[%d].\n", pid_);
    }
  }

 private:
  pid_t pid_;
};