#pragma once
#include <memory>
#include <res.hpp>
#include <string>
#include <unordered_map>
#include <vector>
#include "factory.h"

#define BUILD_UNIQUE_FACTORY(my_factory, constract_product)            \
  my_factory =                                                         \
      std::make_unique<common::Factory<std::string, constract_product, \
                                       constract_product *(*)(void *)>>()

#define DECLARE_UNIQUE_FACTORY(my_factory, constract_product)      \
  std::unique_ptr<common::Factory<std::string, constract_product,  \
                                  constract_product *(*)(void *)>> \
      my_factory



namespace fsm {
using namespace std;


class Protocol;
class Communication {
 public:
  Communication();
  virtual ~Communication() = 0;

  virtual int Send(string name, string data) = 0;
  virtual string Recv(int timeout) = 0;

 private:
  function<void(string)> recv_cb_;
  shared_ptr<Protocol> sp_ptc_;
};

class Protocol {};

class Session {
 public:
  Session(){};
  Res InsertComm(shared_ptr<Communication> sp_comm){};
  Res Send(string name, string data) {}
  Res SendToAll(string data) {}
  Res SendToGroup(vector<string> names, string data) {}
  Res SendExcept(vector<string> names, string data){};
  string Recv(int time_out) {}

 private:
  unordered_map<string, shared_ptr<Communication>> comm_set_;
};

shared_ptr<Communication> MakeCommunication(){

}


}  // namespace fsm
