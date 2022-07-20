/*
 * Copyright (C) Horizon Robotics, Inc. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */
#pragma once
#define LOG printf
#define ERR printf
#include <string>

#include "/data/tangpei/new_repo/hbre/sys-mgr/master_control/third_party/zmq/zmq.h"
struct ZmqArgs {
  enum MODE { kBind, kConnect } mode;
  std::string AddressPath;
};

class ZmqPub final {
 private:
  bool is_init_;
  ZmqArgs args_;
  void* context_;
  void* pub_;
  void* monitor_;

 public:
  ZmqPub(const ZmqArgs args) : is_init_(false), args_(args){};
  ~ZmqPub() {
    zmq_close(pub_);
    zmq_ctx_destroy(context_);
  }
  void Init() {
    if (args_.AddressPath == "") {
      ERR("no zmq ipc file input\n");
    }
    if ((context_ = zmq_ctx_new()) == NULL) {
      ERR("pub context init failed\n");
    }
    if ((pub_ = zmq_socket(context_, ZMQ_PUB)) == NULL) {
      ERR(" pub socket init failed\n");
    }
    int hwm = 10;
    int rc = zmq_setsockopt(pub_, ZMQ_SNDHWM, &hwm, sizeof(hwm));
    if (rc < 0) {
      ERR("set sndhwm failed\n");
    }
    int linger = 1000;
    rc = zmq_setsockopt(pub_, ZMQ_LINGER, &linger, sizeof(linger));
    if (rc < 0) {
      ERR("set linger failed\n");
    }
    int sndbuf = 1024 * 1024;
    rc = zmq_setsockopt(pub_, ZMQ_SNDBUF, &sndbuf, sizeof(sndbuf));
    if (rc < 0) {
      ERR("set sndbuf failed\n");
    }
    if (args_.mode == args_.kBind) {
      if (zmq_bind(pub_, args_.AddressPath.c_str()) < 0) {
        ERR("pub bind failed: %s\n", zmq_strerror(errno));
      }
    } else if (args_.mode == args_.kConnect) {
      if (zmq_connect(pub_, args_.AddressPath.c_str()) < 0) {
        ERR("pub connect failed: %s\n", zmq_strerror(errno));
      }
    } else {
      LOG("mode err, set mode as default: bind");
      if (zmq_bind(pub_, args_.AddressPath.c_str()) < 0) {
        ERR("pub bind failed: %s\n", zmq_strerror(errno));
      }
    }

    // monitor logic
    monitor_ = zmq_socket(context_, ZMQ_PAIR);
    zmq_socket_monitor(pub_, "inproc://zmq_monitor", ZMQ_EVENT_ALL);
    zmq_connect(monitor_, "inproc://zmq_monitor");
    is_init_ = true;
  }

  uint32_t Pub(std::string data) { Pub((void*)data.c_str(), data.size()); }
  uint32_t Pub(void* data, uint32_t len) {
    if (!is_init_) {
      ERR("Pub Fail, Init First.\n");
      return 0;
    }
    zmq_msg_t msg;
    if (zmq_msg_init_size(&msg, len) == 0) {
      ERR("mq_msg_init_size Error\n");
      return 0;
    }
    std::copy(zmq_msg_data(&msg), data, len);
    return zmq_msg_send(&msg, pub_, 0);
  }
};

class ZmqSub final {
 private:
  bool is_init_;
  ZmqArgs args_;
  void* context_;
  void* sub_;
  void* monitor_;
  int timeout_;

 public:
  ZmqSub(const ZmqArgs args) : is_init_(false), args_(args){};
  void Init() {
    if (args_.AddressPath == "") {
      ERR("no zmq ipc file input\n");
    }

    if ((context_ = zmq_ctx_new()) == NULL) {
      ERR("sub context init failed\n");
    }
    if ((sub_ = zmq_socket(context_, ZMQ_SUB)) == NULL) {
      ERR(" sub socket init failed\n");
      zmq_ctx_destroy(context_);
    }
    int hwm = 5;
    int rc = zmq_setsockopt(sub_, ZMQ_RCVHWM, &hwm, sizeof(hwm));
    if (rc < 0) {
      ERR("set recvhwm failed\n");
    }
    int rcvbuf = 1024 * 1024;
    rc = zmq_setsockopt(sub_, ZMQ_RCVBUF, &rcvbuf, sizeof(rcvbuf));
    if (rc < 0) {
      ERR("set recv buf failed\n");
    }

    if (args_.mode == args_.kConnect) {
      if (zmq_connect(sub_, args_.AddressPath.c_str()) < 0) {
        ERR("sub connect failed: %s\n", zmq_strerror(errno));
      }
    } else if (args_.mode == args_.kBind) {
      if (zmq_bind(sub_, args_.AddressPath.c_str()) < 0) {
        ERR("sub bind failed: %s\n", zmq_strerror(errno));
      }
    } else {
      LOG("mode err, set mode as default: bind\n");
      if (zmq_connect(sub_, args_.AddressPath.c_str()) < 0) {
        ERR("sub connect failed: %s\n", zmq_strerror(errno));
      }
    }

    // monitor logic
    monitor_ = zmq_socket(context_, ZMQ_PAIR);
    zmq_socket_monitor(sub_, "inproc://zmq_monitor", ZMQ_EVENT_ALL);
    zmq_connect(monitor_, "inproc://zmq_monitor");
  }
  int Sub(void* data) {
    if (!is_init_) {
      ERR("Sub Fail, Init First.\n");
      return 0;
    }
    if (zmq_setsockopt(sub_, ZMQ_RCVTIMEO, &timeout_, sizeof(timeout_)) < 0) {
      ERR("set time out failed\n");
      return 0;
    }
    zmq_msg_t msg;
    zmq_msg_init(&msg);
    if (zmq_msg_recv(&msg, sub_, 0) < 0) {
      return -1;
    }
    int length = zmq_msg_size(&msg);
    std::copy(data, zmq_msg_data(&msg), length);
    zmq_msg_close(&msg);

    return length;
  }
};