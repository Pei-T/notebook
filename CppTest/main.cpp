// #include <inttypes.h>
// // #include <jsoncpp/json/json.h>
// #include <fcntl.h>
// #include <stdio.h>
// #include <unistd.h>

// #include <functional>
// #include <future>
// #include <iostream>
// #include <sstream>
// #include <string>
// #include <thread>
// #include <vector>

// using namespace std;
// vector<string> FindIp(vector<string>& target_ip);
// bool StringCmpFormEnd(const std::string& basic, const std::string& s);
// // bool RunAtOhterIp(std::string bin_path, std::string ip_dir, bool scp =
// // false);

// vector<string> FindIp(vector<string>& target_ip) {
//   vector<future<bool>> ping_res;
//   vector<string> res;
//   function<bool(string)> ping_to_soc = [](string ip) {
//     char c_str[128] = {0};
//     sprintf(c_str, "ping %s -c 2 -W 1", ip.c_str());
//     auto p_file = popen(c_str, "r");
//     sleep(2);
//     fread(c_str, 1, 128, p_file);
//     string tmp_str(c_str);
//     if (tmp_str.find("seq=1") != string::npos) {
//       return true;
//     }
//     return false;
//   };
//   for (auto i : target_ip) {
//     ping_res.push_back(async(std::launch::async, ping_to_soc, i));
//   }
//   for (uint32_t i = 0; i < ping_res.size(); i++) {
//     auto is_ok = ping_res[i].get();
//     if (is_ok) {
//       res.push_back(target_ip[i]);
//     }
//   }
//   return res;
// }

// bool StringCmpFormEnd(const std::string& basic, const std::string& s) {
//   auto pos = basic.find(s);
//   if (pos == std::string::npos) {
//     return false;
//   } else if (pos == (basic.size() - s.size())) {
//     return true;
//   }
//   return false;
// }

// class RemoteCaller {
//  public:
//   RemoteCaller(string ip, string cmd, string local_dir = "") {
//     ip_ = ip;
//     p_ = NULL;
//     if (local_dir != "") {
//       string remote_dir = cmd.substr(0, cmd.find(" "));
//       SendFile(local_dir, remote_dir);
//     }
// #ifdef UBUNTU
//     cmd_ = "stdbuf -oL ssh root@" + ip_ + " -t '" + cmd + " '\n";
// #else
//     cmd_ = "ssh root@" + ip_ + " -y -t '" + cmd + "'\n";
// #endif
//     cout << cmd_ << endl;
//     p_ = popen(cmd_.c_str(), "w");
//     fd_ = fileno(p_);
//     fcntl(fd_, F_SETFL, 0);
//   }

//   ~RemoteCaller() {
//     cout << "close" << endl;
//     pclose(p_);
//   }

//   int Send(string cmd) {
//     cmd += "\n";
//     cout << cmd;
//     write(fd_, cmd.c_str(), cmd.size());
//     sleep(1);
//     while (fgets(tmp_str_, 1, p_)) {
//       cout << tmp_str_;
//     }
//   }

//   string Recv() {
//     // read(fd_, tmp_str_, -1);
//     // fscanf(p_, "%s\n\0", tmp_str_);
//     while (fgets(tmp_str_, 1, p_)) {
//     }
//     return tmp_str_;
//   }

//   void InitPopen() {}

//   void SendFile(string local_dir, string remote_dir) {
//     string cmd = "scp " + local_dir + " root@" + ip_ + ":" + remote_dir;
//     FILE* p_tmp0 = popen(cmd.c_str(), "r");
//     printf("%s \n", cmd.c_str());
//     pclose(p_tmp0);
// #ifdef UBUNTU
//     string tmp_cmd = "ssh root@" + ip_ + " -T 'chmod " + remote_dir + " '\n";
// #else
//     string tmp_cmd = "ssh root@" + ip_ + " -y 'chmod " + remote_dir + " '\n";
// #endif
//     FILE* p_tmp1 = popen(tmp_cmd.c_str(), "r");
//     pclose(p_tmp1);
//   }

//  private:
//   FILE* p_;
//   int fd_;
//   string ip_, cmd_;
//   char tmp_str_[4 * 1024];
// };

// int main(int argc, char** argv) {
//   // vector<string> ips;
//   // ips.push_back("10.97.100.38");
//   // ips.push_back("192.168.1.10");
//   // ips.push_back("192.168.1.11");
//   // ips.push_back("192.168.1.12");
//   // ips.push_back("10.97.96.41");
//   // auto res = FindIp(ips);
//   // for (auto i : res) {
//   //   cout << i << endl;
//   // }
//   // if (StringCmpFormEnd(ips[4], "41")) {
//   //   printf("HERE\n");
//   // }
//   // Json::Value json_value;
//   // json_value[0] = "test";
//   // json_value[1] = "hello";
//   // json_value[2] = "world";
//   // json_value.append(";");
//   // std::cout << json_value << std::endl;
//   // RunAtOhterIp("ls", "root@192.168.1.10:/userdata/peiT");
//   // Run("192.168.2.10");
//   RemoteCaller caller10("192.168.2.10", "/userdata/Subapp adas_workflow");
//   // RemoteCaller caller11("192.168.2.11", "/userdata/Subapp adas_workflow");
//   // RemoteCaller caller28("192.168.2.28", "/userdata/Subapp adas_workflow");
//   // sleep(1);
//   caller10.Send("Callback");
//   // caller11.Send("Callback");
//   // caller28.Send("Callback");
//   sleep(1);
//   // std::thread(
//   //     [](RemoteCaller* p) {
//   //       while (1) {
//   //         cout << p->Recv() << endl;
//   //         usleep(200000);
//   //       }
//   //     },
//   //     &caller10);
//   // // cout << caller28.Recv() << endl;
//   // caller10.Send("hb_sysmgr_trigger_sys_fault");
//   for (uint32_t i = 0; i < 0; i++) {
//     caller10.Send("hb_sysmgr_trigger_sys_fault");
//     sleep(1);
//     cout << caller10.Recv() << endl;
//   }
//   cout << caller10.Recv() << endl;
//   usleep(200000);
//   // caller28.Send("hb_sysmgr_trigger_ota");
//   sleep(2);
//   // cout << caller28.Recv() << endl;
//   // cout << "sleep done\n" << endl;
//   // sleep(10);
//   return 0;
// }
// #include <fcntl.h>
// #include <stdio.h>
// #include <unistd.h>
// #define READ_TERMINAL 0
// #define WRITE_TERMINAL 1

// int main() {
//   int file_descriptors[2];
//   pid_t pid_f;
//   char PipeBuf[64] = {'a', '0'};
//   int read_ret = 0;
//   pipe(file_descriptors);
//   pid_f = fork();
//   if (pid_f < 0) {
//     printf("fork error!\n");
//     return (1);
//   } else if (pid_f == 0) {
//     //子进程向父进程发一则消息
//     printf("Write in Pipe To FatherProcess!\n");
//     close(file_descriptors[READ_TERMINAL]);
//     sleep(1);
//     write(file_descriptors[WRITE_TERMINAL], "Child Send", sizeof("Child
//     Send"));
//     // open(file_descriptors[READ_TERMINAL]);
//   } else {
//     //父进程接收(读取)消息
//     printf("Read in Pipe From ChildProcess!\n");
//     //通过fcntl()修改为使得读管道数据具有非阻塞的特性
//     int flag = fcntl(file_descriptors[READ_TERMINAL], F_GETFL, 0);
//     flag |= O_NONBLOCK;
//     if (fcntl(file_descriptors[READ_TERMINAL], F_SETFL, flag) < 0) {
//       perror("fcntl");
//       return (1);
//     }
//     close(file_descriptors[WRITE_TERMINAL]);
//     read_ret = read(file_descriptors[READ_TERMINAL], PipeBuf,
//                     sizeof(PipeBuf));  //没阻塞的读
//     printf("Read Message are : %s\n", PipeBuf);

//     read_ret = read(file_descriptors[READ_TERMINAL], PipeBuf,
//     sizeof(PipeBuf)); printf("Read Message are : %s,ret=%d \n", PipeBuf,
//     read_ret);
//     //总结：实践证明默认的读管道具有阻塞特性，若管道内无数据，则一直等待，若无33-38行，则是采用的默认值，读具有阻塞特性
//     //            但是也可以通过fcntl()修改为使得读管道数据具有非阻塞的特性
//     //            当关闭了写端口时，写端口，直接就是写不去，但是不阻塞的
//   }
//   return 0;
// }

// Timeout Test
/**
 * @file TemperatureCallback.cpp
 * @author pei.tang
 * @brief
 * @version 0.1
 * @date 2020-10-11
 *
 * @copyright Copyright (c) 2020
 *
 */

// #include <sysmgr_lib.h>
// #include <unistd.h>

// #include <fstream>
// #include <iostream>
// #include <mutex>
// #include <string>
// #include <thread>
// using namespace std;
// mutex mtx;
// ofstream outfile("/userdata/state.log", ios::app);
// int ret = -1;

// void temp_func(uint8_t para) {
//   streambuf *coutBuf = cout.rdbuf();
//   streambuf *fileBuf = outfile.rdbuf();
//   cout.rdbuf(fileBuf);
//   if (para) {
//     mtx.lock();
//     cout << "this is normal_temp callback" << endl;
//     mtx.unlock();
//     // printf("this is high_temp callback\n");
//   } else {
//     mtx.lock();
//     cout << "this is normal_temp callback" << endl;
//     mtx.unlock();
//     // printf("this is normal_temp callback\n");
//   }
//   outfile.flush();
//   cout.rdbuf(coutBuf);
// }

// void hb_sysmgr_register_over_temperature_entry_func() {
//   streambuf *coutBuf = cout.rdbuf();
//   streambuf *fileBuf = outfile.rdbuf();
//   cout.rdbuf(fileBuf);
//   if (0 == (ret = hb_sysmgr_register_over_temperature_entry(temp_func)))
//   // if (0 == (ret = hb_sysmgr_register_over_temperature_entry(0)))
//   // if (0 == (ret = hb_sysmgr_register_over_temperature_entry(NULL))))
//   // if (0 == (ret = hb_sysmgr_register_over_temperature_entry()))
//   // if (0 == (ret = hb_sysmgr_register_over_temperature_entry(temp_func,
//   0)))
//   {
//     mtx.lock();
//     cout << "hb_sysmgr_register_over_temperature_entry success" << endl;
//     mtx.unlock();
//   } else {
//     mtx.lock();
//     cout << "hb_sysmgr_register_over_temperature_entry fail" << endl;
//     mtx.unlock();
//   }
//   outfile.flush();
//   cout.rdbuf(coutBuf);
// }

// int main(int argc, char **argv) {
//   std::string name = "adas_workflow";
//   std::thread t;
//   int mode = 15;
//   ret = hb_register_proc(name, mode);
//   if ((atoi(argv[1]) & 2) == 2) {
//     std::cout << "before joinable: " << t.joinable() << '\n';
//     t = std::thread(hb_sysmgr_register_over_temperature_entry_func);
//     std::cout << "after joinable: " << t.joinable() << '\n';
//   }
//   if (1 == (atoi(argv[1]) & 1)) {
//     hb_sysmgr_register_over_temperature_entry_func();
//   }
//   if ((atoi(argv[1]) & 2) == 2) {
//     t.join();
//     std::cout << "after joining, joinable: " << t.joinable() << '\n';
//     // add_thread_func();
//     // close_thread_func();
//   }
//   while (1) {
//     sleep(1);
//   }
// }

// #include <unistd.h>

// #include <future>
// #include <iostream>
// #include <thread>

// #include "../utils/thread_safe_set.h"
// using namespace std;
// void speed_cin(ThreadSafeSet<string>* set) {
//   string tmp_str;
//   while (cin >> tmp_str) {
//     if (tmp_str == "clear") {
//       set->Clear();
//     } else {
//       set->Erase(tmp_str);
//     }
//   }
// }
// int main() {
//   ThreadSafeSet<string> set;
//   // set.Insert("hello");
//   // set.Insert("world");
//   // set.Insert("a");
//   thread th(speed_cin, &set);
//   int res = set.WaitForZeroSize(10000);
//   if (res == true) {
//     cout << "will done" << endl;
//   } else {
//     auto tmp_set = set.GetCopy();
//     cout << "bad done:" << endl;
//     for (auto i : tmp_set) {
//       cout << "\t" << i << endl;
//     }
//   }
// }
// #include <chrono>
// #include <future>
// #include <iostream>
// #include <numeric>
// #include <thread>
// #include <vector>
// using namespace std;
// class Test {
//  public:
//   Test() { future_ = promise_.get_future(); }
//   ~Test() {}
//   void input() {
//     int tmp_num = 0, total = 0;
//     for (uint32_t i = 0; i < 5; i++) {
//       cin >> tmp_num;
//       total += tmp_num;
//     }
//     promise_.set_value(total);
//   }
//   void output() {
//     auto status = future_.wait_for(std::chrono::milliseconds(5000));
//     if (status == future_status::ready) {
//       cout << "total res: " << future_.get() << endl;
//     } else if (status == future_status::timeout) {
//       cout << "timeout" << endl;
//     } else {
//     }
//   }

//  private:
//   std::promise<int> promise_;
//   std::future<int> future_;
// };
// void CinFunc(Test* p) { p->input(); }

// int main() {
//   Test test;
//   thread th(CinFunc, &test);
//   test.output();
//   th.join();
// }
#include <unistd.h>

#include <condition_variable>
#include <functional>
#include <future>
#include <iostream>
#include <map>
#include <mutex>
#include <string>
#include <thread>
#include <vector>

#include "../utils/threadpool.h"
template <class Fn, class... Args>
std::function<bool()> CancelableCall(uint32_t delay, Fn&& fn, Args&&... args) {
  auto sp_pm = std::make_shared<std::promise<int>>();
  auto sp_atm = std::make_shared<std::atomic<bool>>(false);
  auto sp_func = std::make_shared<std::function<void()>> =
      std::bind(std::forward<Fn>(fn), std::forward<Args>(args)...);

  auto res = [](std::shared_ptr<std::promise<int>> sp_pm,
                std::shared_ptr<std::atomic<bool>> sp_atm) {
    sp_pm->set_value(true);
    return sp_atm->load();
  };
  auto work = [](std::shared_ptr<std::promise<int>> sp_pm,
                 std::shared_ptr<std::function<void()>> sp_func,
                 std::shared_ptr<std::atomic<bool>> sp_atm, uint32_t delay) {
    auto state = sp_pm->get_future().wait_for(std::chrono::milliseconds(delay));
    if (state == std::future_status::ready) {
      sp_atm->store(true);
    } else {
      (*sp_func)();
    }
  };
  std::thread th(work, sp_pm, sp_func, sp_atm, delay);
  return res;
}

class Timer {
 public:
  Timer() {
    run_flag_.store(true);
    th_ = std::thread(std::bind(&Timer::BackFunc_, this));
  }

  ~Timer() {
    run_flag_.store(false);
    funcs_[now_()] = std::make_shared<std::function<void()>>([]() {});
    cv_.notify_all();
    th_.join();
  }

  void InsertFunc(uint32_t time, std::function<void()> f) {
    auto sp_f = std::make_shared<std::function<void()>>(f);
    funcs_[now_() + std::chrono::milliseconds(time)] = sp_f;
    std::unique_lock<std::mutex> lck(mtx_);
    cv_.notify_all();
  }

  void InsertFunc(uint32_t time, std::shared_ptr<std::function<void()>> f) {
    funcs_[now_() + std::chrono::milliseconds(time)] = f;
    std::unique_lock<std::mutex> lck(mtx_);
    cv_.notify_all();
  }

 private:
  std::thread th_;
  std::mutex mtx_;
  std::condition_variable cv_;
  std::atomic<bool> run_flag_;
  using time_point = std::chrono::_V2::steady_clock::time_point;
  std::map<time_point, std::shared_ptr<std::function<void()>>> funcs_;
  inline std::chrono::_V2::steady_clock::time_point now_() {
    return std::chrono::steady_clock::now();
  }
  void BackFunc_() {
    while (run_flag_.load()) {
      std::unique_lock<std::mutex> lck(mtx_);
      cv_.wait(lck, [=]() -> bool { return funcs_.size() != 0; });
      lck.unlock();
      std::this_thread::sleep_until(funcs_.begin()->first);
      if (*(funcs_.begin()->second) != nullptr) (*(funcs_.begin()->second))();
      funcs_.erase(funcs_.begin());
    }
  }
};

template <class T>
class Node {
 public:
  enum State { UNKNOWN, HIGH, LOW };
  Node() {}
  Node(Timer* tw, T high_val, uint32_t high_times, uint32_t high_time,
       T low_val, uint32_t low_times, uint32_t low_time,
       State default_state = State::LOW) {
    tw_ = tw;
    HighVal = high_val;
    HighCount = high_times;
    HighTimeout = high_time;
    LowVal = low_val;
    LowCount = low_times;
    LowTimeout = low_time;
    LastState = new (State);
    *LastState = default_state;
    tmp_state_ = default_state;
    LowCbSwither = std::make_shared<std::function<void()>>();
    HighCbSwither = std::make_shared<std::function<void()>>();
  }
  void SetHighCb(std::function<void()> f) {
    HighCb = std::bind(
        [](std::function<void()> f, Node::State* p) {
          f();
          *p = Node::State::HIGH;
        },
        f, LastState);
  }
  void SetLowCb(std::function<void()> f) {
    LowCb = std::bind(
        [](std::function<void()> f, Node::State* p) {
          f();
          *p = Node::State::LOW;
        },
        f, LastState);
  }
  void CheckValue(T val) {
    if (val < HighVal && *LastState != HIGH && tmp_state_ != HIGH) {
      LastVal = val;
      return;
    }

    if (LastVal < HighVal && val >= HighVal && *LastState != State::HIGH) {
      tmp_state_ = Node::State::HIGH;
      // printf("CASE1\n");
    } else if (LastVal >= LowVal && val < LowVal && *LastState != State::LOW) {
      tmp_state_ = Node::State::LOW;
      // printf("CASE2\n");
    } else if (tmp_state_ == Node::State::HIGH && val < HighVal) {
      tmp_state_ = Node::State::UNKNOWN;
      // printf("CASE3\n");
    } else if (tmp_state_ == Node::State::LOW && val > LowVal) {
      tmp_state_ = Node::State::UNKNOWN;
      // printf("CASE4\n");
    }

    if (tmp_state_ == Node::State::HIGH) {
      HighHock();
      // printf("CASE5\n");
    } else if (tmp_state_ == Node::State::LOW) {
      LowHock();
      // printf("CASE6\n");
    } else {
      ClearHock();
      // printf("CASE7\n");
    }
    LastVal = val;
  }

 private:
  Timer* tw_;
  State* LastState;
  State tmp_state_;
  T LowVal, HighVal, LastVal;
  uint32_t LowCount, HighCount, TmpLowCount, TmpHighCount;
  uint32_t HighTimeout, LowTimeout;
  std::function<void()> LowCb, HighCb;
  std::shared_ptr<std::function<void()>> LowCbSwither, HighCbSwither;

  void HighHock() {
    TmpHighCount++;
    TmpLowCount = 0;
    *LowCbSwither = (std::function<void()>());
    if (TmpHighCount == HighCount && *LastState != HIGH) {
      *HighCbSwither = HighCb;
      tw_->InsertFunc(HighTimeout, HighCbSwither);
      // printf("Set high\n");
    }
  }
  void LowHock() {
    TmpHighCount = 0;
    TmpLowCount++;
    *HighCbSwither = (std::function<void()>());
    if (TmpLowCount == LowCount && *LastState != LOW) {
      *LowCbSwither = LowCb;
      tw_->InsertFunc(LowTimeout, LowCbSwither);
      // printf("Set low\n");
    }
  }
  void ClearHock() {
    TmpHighCount = 0;
    TmpLowCount = 0;
    *HighCbSwither = (std::function<void()>());
    *LowCbSwither = (std::function<void()>());
    // printf("Clear all\n");
  }
};

template <class P>
class DebounceServer {
 public:
  DebounceServer(){};

  void Insert(std::string name, P HighValue, std::function<void()> high_f,
              std::function<void()> low_f) {
    Node<P> tmp(&tw, HighValue, 1, 1000, HighValue, 1, 1000);
    tmp.SetHighCb(high_f);
    tmp.SetLowCb(low_f);
    nodes_.insert(std::make_pair(name, tmp));
  }
  void Insert(std::string name, P Highvalue, uint32_t high_times,
              uint32_t high_time, std::function<void()> high_f, P low_val,
              uint32_t low_times, uint32_t low_time,
              std::function<void()> low_f) {
    Node<P> tmp(&tw, Highvalue, high_times, high_time, low_val, low_times,
                low_time);
    tmp.SetHighCb(high_f);
    tmp.SetLowCb(low_f);
    nodes_.insert(std::make_pair(name, tmp));
  }
  void InsertBool(std::string name, uint32_t high_times, uint32_t high_time,
                  std::function<void()> high_f, uint32_t low_times,
                  uint32_t low_time, std::function<void()> low_f) {
    Node<P> tmp(&tw, (P)1, high_times, high_time, (P)0, low_times, low_time);
    tmp.SetHighCb(high_f);
    tmp.SetLowCb(low_f);
    nodes_.insert(std::make_pair(name, tmp));
  }
  void CheckVal(std::string name, P val) { nodes_[name].CheckValue(val); }
  void SetHighCb(std::string name, std::function<void()> high_f) {
    auto it = nodes_.find(name);
    if (it != nodes_.end()) {
      it->second.SetHighCb(high_f);
    }
  }
  void SetLowCb(std::string name, std::function<void()> high_f) {
    auto it = nodes_.find(name);
    if (it != nodes_.end()) {
      it->second.SetLowCb(high_f);
    }
  }

 private:
  Timer tw;
  std::map<std::string, Node<P>> nodes_;
};

int main() {
  DebounceServer<int> Server1;
  auto func1 = []() { printf("\tHIGH FUNC\n"); };
  auto func2 = []() { printf("\tLOW FUNC\n"); };
  Server1.Insert("test", 5, 2, 10, func1, 4, 2, 10, func2);
  int tmp_num;
  while (true) {
    tmp_num = rand() % 10;
    printf("%d\n", tmp_num);
    Server1.CheckVal("test", tmp_num);
    sleep(1);
  }

  return 0;
}

// #include <chrono>
// #include <iostream>
// #include <thread>
// auto now() { return std::chrono::steady_clock::now(); }
// auto awake_time() {
//   using std::chrono::operator""ms;
//   return now() + 2000ms;
// }
// int main() {
//   std::cout << "Hello, waiter...\n" << std::flush;
//   const auto start{now()};
//   std::this_thread::sleep_until(awake_time());
//   std::chrono::duration<double, std::milli> elapsed{now() - start};
//   std::cout << "Waited " << elapsed.count() << " ms\n";
// }