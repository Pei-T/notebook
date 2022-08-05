// Copyright (C) Horizon Robotics, Inc. - All Rights Reserved
// Unauthorized copying of this file, via any medium is strictly prohibited
// Proprietary and confidential

#include <iostream>
#include <memory>
class Test {
 public:
  Test(int i) {  }
  void Info() { printf("%d\t%d\t%d\n", &sp_, &(*sp_), *sp_); }

 private:
  std::shared_ptr<int> sp_;
};

int main() {
  Test t1(1);
  Test t2(t1);

  t1.Info();
  t2.Info();
}