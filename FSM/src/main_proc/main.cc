#include <signal.h>
#include <unistd.h>

#include <iostream>

#include "res.hpp"
void Exit(int no) { printf("Exit  %d\n", no); }
Res Init() {
  signal(SIGINT, Exit);
  return Res::kOK();
}

int main() {
  if (Init().IsOk()) return -1;
}