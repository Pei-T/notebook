# Move
本文档验证一个类在函数传递时，函数返回时，进入STL时将发生哪些构造函数。
## 1. 约定

```cpp
// 左值
int a =10 ;
Test A;
func2(Test&& t)// 无论用什么方式传进来的参数，都是左值。
// 左值引用
int& b = a;
Test& B = A;
// 右值
Test();
10
func2() //通常函数返回值为一右值。
// 右值引用
int&& c = 10;
Test&& C = Test();
```

#2 参数传递
1. void func2(Test t)：无论传入左值，右值，左值引用，右值引用，会调用一次**构造函数**。
传入Test类型（无论左值右值），调用复制构造函数。传入数字，调用默认构造函数。
2. void func2(Test& t)：只可传入左值，左值引用，不会调用构造函数；
3. void func2(Test&& t)：只可传入右值，右值引用,不会调用构造函数；
#3 返回值
Test& func2(Test&& t)：返回引用，不会调用构造函数。
Test func2(Test&& t)：返回右值，会调用一次**构造函数**，返回数值，调用默认构造函数，返回Test，调用复制构造函数。

#4 进入vector
push_back(左值)： 调用**复制构造函数**
push_back(右值)： 调用**移动构造函数**
push_back(数值)： 调用**默认构造函数+移动构造函数**
data[0]=左值：    调用**等于函数**


```cpp
#include <unistd.h>

#include <algorithm>
#include <iostream>
#include <map>
#include <string>
#include <vector>
// #include "../LibTest/funcs.hpp"
// #include "factory.h"
// #include "res.hpp"

// 如何将一个类放到容器中，并且全程不调用构造函数。

class Test {
 public:
  Test() : a_(0) { printf("Default\n"); }
  Test(int a) : a_(a) { printf("Default2\n"); }
  Test(const Test& t) {
    a_ = t.a_;
    printf("Copy\n");
  }
  Test(Test&& t) {
    a_ = t.a_;
    printf("Move\n");
  }
  Test& operator=(const Test& other) {
    printf("=\n");
    this->a_ = other.a_;
    return *this;
  }
  void SayHello() { printf("Hello %d\n", a_); }
  void A(int a) { a_ = a; }

 private:
  int a_;
};

Test& func1(Test& t) {
  // std::vector<Test> test_vec;
  // test_vec.push_back(std::move(t));
  static Test res;
  return res;
}

void func2(Test& t) {
  t.SayHello();
  t.A(1);
  t.SayHello();
}

int main() {
  Test a(1);
  auto& b = a;
  // std::map<int, Test> data;
  // // data[1] = a;  // Default =
  // data.insert(std::make_pair(1, std::move(a)));

  std::vector<Test> data;
  data.push_back(std::move(a));
  // data[0].SayHello();
  printf("Now Get a Test form vector:\n");
  Test && tmp=2;
  func2(tmp);
}
```