#include <inttypes.h>
#include <jsoncpp/json/json.h>
#include <stdio.h>
#include <unistd.h>

#include <functional>
#include <future>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
vector<string> FindIp(vector<string>& target_ip);
bool StringCmpFormEnd(const std::string& basic, const std::string& s);
// bool RunAtOhterIp(std::string bin_path, std::string ip_dir, bool scp =
// false);

vector<string> FindIp(vector<string>& target_ip) {
  vector<future<bool>> ping_res;
  vector<string> res;
  function<bool(string)> ping_to_soc = [](string ip) {
    char c_str[128] = {0};
    sprintf(c_str, "ping %s -c 2 -W 1", ip.c_str());
    auto p_file = popen(c_str, "r");
    sleep(2);
    fread(c_str, 1, 128, p_file);
    string tmp_str(c_str);
    if (tmp_str.find("seq=1") != string::npos) {
      return true;
    }
    return false;
  };
  for (auto i : target_ip) {
    ping_res.push_back(async(std::launch::async, ping_to_soc, i));
  }
  for (uint32_t i = 0; i < ping_res.size(); i++) {
    auto is_ok = ping_res[i].get();
    if (is_ok) {
      res.push_back(target_ip[i]);
    }
  }
  return res;
}

bool StringCmpFormEnd(const std::string& basic, const std::string& s) {
  auto pos = basic.find(s);
  if (pos == std::string::npos) {
    return false;
  } else if (pos == (basic.size() - s.size())) {
    return true;
  }
  return false;
}

bool RunAtOhterIp(std::string bin_path, std::string ip_dir, bool scp = false) {
  char cmd[256];
  int pos1 = bin_path.find_last_of("/");
  int pos2 = ip_dir.find(":");
  string bin_head = bin_path.substr(0, pos1);
  string bin_tail = bin_path.substr(pos1 + 1, bin_path.size() - pos1 - 1);
  string ip_head = ip_dir.substr(0, pos1);
  string ip_tail = ip_dir.substr(pos1 + 1, ip_dir.size() - pos1 - 1);
  string scp_cmd = "scp " + bin_path + " " + ip_dir;
  if (scp) {
    // sprintf(cmd, "%s;ssh %s -t 'chmod 777 %s;%s'", scp_cmd.c_str(),
    //         sub_dir.c_str(), sub_dir.c_str(), sub_dir.c_str());
  } else {
    // sprintf(cmd, "ssh %s -t 'cd %s;%s'", ip_head.c_str(), bin_tail.c_str());
  }
  // printf("%s\n", cmd);
}
int main(int argc, char** argv) {
  // vector<string> ips;
  // ips.push_back("10.97.100.38");
  // ips.push_back("192.168.1.10");
  // ips.push_back("192.168.1.11");
  // ips.push_back("192.168.1.12");
  // ips.push_back("10.97.96.41");
  // auto res = FindIp(ips);
  // for (auto i : res) {
  //   cout << i << endl;
  // }
  // if (StringCmpFormEnd(ips[4], "41")) {
  //   printf("HERE\n");
  // }
  // Json::Value json_value;
  // json_value[0] = "test";
  // json_value[1] = "hello";
  // json_value[2] = "world";
  // json_value.append(";");
  // std::cout << json_value << std::endl;
  RunAtOhterIp("ls", "root@192.168.1.10:/userdata/peiT");
  return 0;
}

