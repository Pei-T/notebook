#include <iostream>
#include <memory>
#include <string>
int main(int argc, char** argv) {
  printf("HelloWorld\n");
  std::string name = "hello";
  auto sp_var = std::make_shared<std::string>("world");

  std::cout << name << std::endl;
  std::cout << *sp_var << std::endl;
  return 0;
}