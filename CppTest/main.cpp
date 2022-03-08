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

#include <sysmgr_lib.h>
#include <unistd.h>

#include <fstream>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
using namespace std;
mutex mtx;
ofstream outfile("/userdata/state.log", ios::app);
int ret = -1;

void temp_func(uint8_t para) {
  streambuf *coutBuf = cout.rdbuf();
  streambuf *fileBuf = outfile.rdbuf();
  cout.rdbuf(fileBuf);
  if (para) {
    mtx.lock();
    cout << "this is normal_temp callback" << endl;
    mtx.unlock();
    // printf("this is high_temp callback\n");
  } else {
    mtx.lock();
    cout << "this is normal_temp callback" << endl;
    mtx.unlock();
    // printf("this is normal_temp callback\n");
  }
  outfile.flush();
  cout.rdbuf(coutBuf);
}

void hb_sysmgr_register_over_temperature_entry_func() {
  streambuf *coutBuf = cout.rdbuf();
  streambuf *fileBuf = outfile.rdbuf();
  cout.rdbuf(fileBuf);
  if (0 == (ret = hb_sysmgr_register_over_temperature_entry(temp_func)))
  // if (0 == (ret = hb_sysmgr_register_over_temperature_entry(0)))
  // if (0 == (ret = hb_sysmgr_register_over_temperature_entry(NULL))))
  // if (0 == (ret = hb_sysmgr_register_over_temperature_entry()))
  // if (0 == (ret = hb_sysmgr_register_over_temperature_entry(temp_func, 0)))
  {
    mtx.lock();
    cout << "hb_sysmgr_register_over_temperature_entry success" << endl;
    mtx.unlock();
  } else {
    mtx.lock();
    cout << "hb_sysmgr_register_over_temperature_entry fail" << endl;
    mtx.unlock();
  }
  outfile.flush();
  cout.rdbuf(coutBuf);
}

int main(int argc, char **argv) {
  std::string name = "adas_workflow";
  std::thread t;
  int mode = 15;
  ret = hb_register_proc(name, mode);
  if ((atoi(argv[1]) & 2) == 2) {
    std::cout << "before joinable: " << t.joinable() << '\n';
    t = std::thread(hb_sysmgr_register_over_temperature_entry_func);
    std::cout << "after joinable: " << t.joinable() << '\n';
  }
  if (1 == (atoi(argv[1]) & 1)) {
    hb_sysmgr_register_over_temperature_entry_func();
  }
  if ((atoi(argv[1]) & 2) == 2) {
    t.join();
    std::cout << "after joining, joinable: " << t.joinable() << '\n';
    // add_thread_func();
    // close_thread_func();
  }
  while (1) {
    sleep(1);
  }
}
