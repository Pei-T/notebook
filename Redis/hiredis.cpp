
#include <hiredis/hiredis.h>
#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include <memory>
#include <sstream>
#include <string>

#define redis_context redisContext
#define redis_reply redisReply
#include <random>
std::random_device rd;  // rd();
template <class T>
class RedisQueue {
 private:
  redis_context *conn_;
  std::string key_;

 public:
  RedisQueue(redis_context *conn, std::string key) : conn_(conn), key_(key) {}
  ~RedisQueue() {}
  bool LeftPush(T data) {
    auto reply = redisCommand(conn_, "LPUSH %s %s", key_.c_str(),
                              std::to_string(data).c_str());
    if (reply == NULL) {
      return false;
    }
    return true;
  }
  bool RightPush(T data) {
    auto reply = redisCommand(conn_, "RPUSH %s %s", key_.c_str(),
                              std::to_string(data).c_str());
    if (reply == NULL) {
      return false;
    }
    return true;
  }
  bool LeftPop(T &data) {
    auto reply = (redisReply *)redisCommand(conn_, "LPOP %s", key_.c_str());
    if (reply == NULL) return false;
    // #include <sstream>
    std::stringstream ss(reply->str);
    ss >> data;
    return true;
  }
  bool RightPop(T &data) {
    auto reply = (redisReply *)redisCommand(conn_, "RPOP %s", key_.c_str());
    if (reply == NULL) return false;
    // #include <sstream>
    std::stringstream ss(reply->str);
    ss >> data;
    return true;
  }
};

template <class T>
class RedisObj {
 private:
  redis_context *conn_;
  std::string key_;

 public:
  RedisObj(redis_context *conn, std::string key) : conn_(conn), key_(key) {}
  ~RedisObj() {}
  bool Set(const T &obj) {
    auto reply = redisCommand(conn_, "SET %s %s", key_.c_str(),
                              std::to_string(obj).c_str());
    if (reply == NULL) {
      return false;
    }
    return true;
  }
  bool Get(T &obj) {
    auto reply = (redisReply *)redisCommand(conn_, "GET %s", key_.c_str());
    if (reply == NULL) return false;
    // #include <sstream>
    std::stringstream ss(reply->str);
    ss >> obj;
    return true;
  }
};
int Func(redis_context *p) {
  printf("HelloWorld\n");
  RedisObj<int> redis_obj(p, "Obj:test");
  int tmp = 90;
  redis_obj.Set(tmp);
  tmp = 0;
  redis_obj.Get(tmp);
  std::cout << tmp << std::endl;
  return 0;
}
// Hello Redis
int main(int argc, char **argv) {
  struct timeval timeout;
  redis_context *conn;
  redis_reply *reply;
  char *hostname;
  int port;
  // char *password;
  // password = const_cast<char *>("");

  hostname = const_cast<char *>("0.0.0.0");
  port = 6379;
  timeout.tv_sec = 1;
  timeout.tv_usec = 500000;

  /*建立连接*/
  conn = redisConnectWithTimeout(hostname, port, timeout);
  if (conn == NULL || conn->err) {
    if (conn) {
      printf("Connection error: %s\n", conn->errstr);
      redisFree(conn);
    } else {
      printf("Connection error: can't allocate redis context\n");
    }
    exit(1);
  }

  /*身份认证*/
  /*reply = redisCommand(conn, "AUTH %s", password);
  printf("AUTH: %s\n", reply->str);
  freeReplyObject(reply);*/

  /*设置缓存变量*/
  reply = (redisReply *)redisCommand(conn, "SET %s %s", "welcome",
                                     "Hello, DCS for Redis!");
  printf("SET: %s\n", reply->str);
  freeReplyObject(reply);
  Func(conn);
  /*获取变量值*/
  reply = (redisReply *)redisCommand(conn, "GET welcome");
  printf("GET welcome: %s\n", reply->str);
  freeReplyObject(reply);

  /*删除变量*/
  reply = (redisReply *)redisCommand(conn, "DEL welcome");
  printf("DEL: %s\n", reply->str);
  freeReplyObject(reply);

  /*关闭连接*/
  redisFree(conn);

  return 0;
}