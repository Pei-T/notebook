/*
 * Copyright (C) Horizon Robotics, Inc. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */
#pragma once
#include <iostream>
#include <map>
#include <memory>
#include <string>
#define LOG_INFO     \
  printf("[INFO] "); \
  printf
#define LOG_ERR       \
  printf("[ERROR] "); \
  printf

#define REGISTER(x) RegisterHelper<x>* p_##x = new RegisterHelper<x>()

namespace fm {
class State;
class StateManager;

class State {
 public:
  State(std::string name)
      : name_(name){
            // StateManager::Instance()->Push(name_, this);
        };
  ~State() = default;
  State(const State& state) = delete;
  State& operator=(const State& state) = delete;

  virtual int OnEntry() = 0;
  virtual int OnExit() = 0;
  virtual int CheckCondition() = 0;
  virtual int HandleMessage(void* data) = 0;
  virtual int Info() = 0;

  std::string Name() { return name_; }

 private:
  std::string name_;
};

class StateManager {
 public:
  static std::shared_ptr<StateManager> Instance() {
    static std::shared_ptr<StateManager> sp(new StateManager);
    return sp;
  }
  StateManager() = default;
  StateManager(const StateManager& sm) = delete;
  StateManager& operator=(const StateManager& sm) = delete;
  StateManager(const StateManager&& sm) = delete;

  void Push(std::string name, State* p) { states_map[name] = p; }
  void Info() {
    for (auto&& i : states_map) {
      i.second->Info();
    }
  }

 private:
  std::map<std::string, State*> states_map;
};

template <class T>
class RegisterHelper {
 public:
  RegisterHelper() {
    State* tmp = new T();
    StateManager::Instance()->Push(tmp->Name(), tmp);
  }
};
}  // namespace fm