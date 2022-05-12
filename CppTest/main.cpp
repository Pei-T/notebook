#include <unistd.h>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

// #include "../LibTest/funcs.hpp"
// #include "factory.h"
// #include "res.hpp"

int func1(uint32_t a){
  int b=0;
  for(uint32_t i=0;i<a;i++){
    b=a;
    printf("hello %d\n",b);
  }
  return 1;
}
int main() {
  std::vector<std::string> data;
  data.push_back("Hello");
  data.push_back("world");
  std::cout << data[0] << data[1] << std::endl;
  func1(4);
  int c=20;
  auto tmp_str = data[2];
  std::cout << tmp_str << std::endl;
}
