#pragma once
#include <functional>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <unordered_map>
using namespace std;
class SendMap {
 public:
  template <class Terminal>
  int AddDestination(Terminal terminal) {}
  int DelDestination(string name) {}
  int SendAll(const char* p, uint32_t size) {}
  int SendTo(string name, const char* p, uint32_t size) {}
  int SendTo(vector<string> names, const char* p, uint32_t size) {}
  int SendExcept(vector<string> names, const char*, uint32_t size) {}

 private:
  struct TerminalSendAndRead {
    function<int(const char*, uint32_t)>* send;
    function<int(char*, int)>* read;
  };
  unordered_map<string, TerminalSendAndRead> terminal_map_;
};
