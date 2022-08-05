
#include <hiredis/hiredis.h>
#include <stdio.h>
#include <stdlib.h>

#include <string>

#define redis_context redisContext
#define redis_reply redisReply

struct RedisArgs {
  std::string Addr;
  uint32_t Port;
  std::string ID;
  std::string Password;
};

class RedisClient : public enable_shared_from_this<RedisClient> {
 public:
  RedisClient()
      : args_({"0.0.0.0", 6379, {1, 0}, "", ""}), state_(kUnConnect) {}
  RedisClient(RedisArgs args) : args_(args), state_(kUnConnect) {}

  RedisClient(const RedisClient &redis_client) = delete;
  RedisClient(RedisClient &&redis_client) = delete;
  RedisClient &operator=(const RedisClient &redis_client) = delete;

  ~RedisClient() { redisFree(conn_); }

  enum RedisState { kError = -1, kUnConnect, kDone };
  RedisState State() { return state_; }

  shared_ptr<RedisClient> SharedPtr() { return shared_from_this(); }

  bool Connect() {
    conn_ = redisConnect(hostname, port, timeout);
    if (conn_ == NULL || conn_->err) {
      if (conn_) {
        printf("Connection error: %s\n", conn_->errstr);
        redisFree(conn_);
      } else {
        printf("Connection error: can't allocate redis context\n");
      }
      state_ = kError;
      return false;
    }
    state_ = kDone;
    return true;
  }
  bool IdConfirm() {
    reply =
        redisCommand(conn, "%s %s", args_.ID.c_str(), args_.Password.c_str());
    if (!reply) {
      printf("AUTH: %s\n", (redis_reply *)reply->str);
      freeReplyObject(reply);
    } else {
      printf("ID Wrong\n");
    }
  }
  redis_reply *Command(std::string cmd) {
    return (redis_reply *)redisCommand(conn, cmd.c_str());
  }

 private:
  RedisState state_;
  redisContext *conn_;
  redisReply *reply_;
  RedisArgs args_;
};

template <class T>
class RedisDeque {
  RedisDeque() : name_("defaule:queue") {}
  RedisDeque(std::string name) : name_(name) {}
  RedisDeque(std::string name, RedisArgs args) : name_(name), args_(args) {}
  bool LPush(T obj) {}
  bool RPush(T obj) {}
  T LPop() {}
  T RPop() {}

 private:
  std::string name_;
  RedisArgs args_;
  std::shared_ptr<RedisClient> sp_redis_client_;
};

int main(int argc, char **argv) {
  struct timeval timeout;
  redis_context *conn;
  redis_reply *reply;
  char *hostname;
  char *password;
  int port;
  int j;

  if (argc < 3) {
    printf("Usage: example {instance_ip_address} 6379 {password}\n");
    return (0);
  }

  hostname = argv[1];
  port = std::atoi(argv[2]);
  password = argv[3];
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