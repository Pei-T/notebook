
#include <functional>
#include <iostream>
#include <map>
#include <string>
enum PowerMode { kOn = 0, kOff };
struct Diag {
  int DiagId;
  int DiagMsg;
};

std::map<std::string, std::function<void(void*)>> g_func_map;
void SetCallback(std::string&& name, std::function<void(void*)>&& f) {
  g_func_map[name] = f;
}
void SetPowerCallback(std::function<void(PowerMode)> f) {
  std::function<void(void*)> tmp_func = [=](void* p) {
    PowerMode power_mode = *((PowerMode*)p);
    f(power_mode);
  };
  SetCallback("power", std::move(tmp_func));
}
void SetDiagCallback(std::function<void(Diag)> f) {
  std::function<void(void*)> tmp_func = [=](void* p) {
    Diag diag_msg = *((Diag*)p);
    f(diag_msg);
  };
  SetCallback("diag", std::move(tmp_func));
}

int main() {
  std::function<void(PowerMode)> power_func = [](PowerMode power_mode) {
    if (power_mode == kOn) {
      printf("power_mode == kOn\n");
    } else {
      printf("power_mode == kOff\n");
    }
  };
  std::function<void(Diag)> diag_func = [](Diag diag_msg) {
    printf("DiagId:%d DiagMsg:%d \n", diag_msg.DiagId, diag_msg.DiagMsg);
  };
  SetPowerCallback(power_func);
  SetDiagCallback(diag_func);
  PowerMode tmp_mode = kOff;
  Diag tmp_diag = {12, 23};
  g_func_map["diag"](&tmp_diag);
  g_func_map["power"](&tmp_mode);
}