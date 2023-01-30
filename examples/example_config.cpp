/****************************************************************************
Copyright (c) 2018, likepeng
All rights reserved.

Author: likepeng <likepeng0418@163.com>
****************************************************************************/
#include <chrono>
#include <thread>

#include <glog/logging.h>

#include "myframe/msg.h"
#include "myframe/actor.h"
#include "myframe/worker.h"

class ExampleActorConfig : public myframe::Actor {
 public:
  int Init(const char* param) override {
    auto conf = GetConfig();
    LOG(INFO) << GetActorName() << " conf " << conf->toStyledString();
    return 0;
  }

  void Proc(const std::shared_ptr<const myframe::Msg>& msg) override {
  }
};

class ExampleWorkerConfig : public myframe::Worker {
 public:
  ExampleWorkerConfig() {}
  virtual ~ExampleWorkerConfig() {}

  void Init() override {
    auto conf = GetConfig();
    LOG(INFO) << GetWorkerName() << " conf " << conf->toStyledString();
  }
  void Run() override {
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
  }
};

/* 创建actor实例函数 */
extern "C" std::shared_ptr<myframe::Actor> my_actor_create(
    const std::string& actor_name) {
  return std::make_shared<ExampleActorConfig>();
}

/* 创建worker实例函数 */
extern "C" std::shared_ptr<myframe::Worker> my_worker_create(
    const std::string& worker_name) {
  return std::make_shared<ExampleWorkerConfig>();
}