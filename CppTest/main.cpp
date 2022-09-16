#include <iostream>
#include <memory>
#include <string>

class Test {
 public:
  // Constructors All.
  Test() { std::cout << "Constructor" << std::endl; }
  Test(Test&& other) { std::cout << "move" << std::endl; }
  Test(const Test& other) { std::cout << "copy" << std::endl; }
  Test& operator=(const Test& other) {
    std::cout << "=copy" << std::endl;
    return *this;
  }
  Test& operator=(Test&& other) {
    std::cout << "=move" << std::endl;
    return *this;
  }

  ~Test() { std::cout << "~Constructor" << std::endl; };
};

int Func(auto&& a) {
  printf("HelloWorld\n");
  auto b = a;
  return 0;
}

int main(int argc, char** argv) {
  auto a = Test();
  auto b = Test();
  b = Test();
}
