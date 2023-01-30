/****************************************************************************
Copyright (c) 2018, likepeng
All rights reserved.

Author: likepeng <likepeng0418@163.com>
****************************************************************************/

#pragma once
#include <pthread.h>

#include <atomic>
#include <list>
#include <memory>
#include <string>
#include <unordered_map>

#include "myframe/macros.h"

namespace myframe {

class Msg;
class WorkerContext;
class WorkerContextManager final {
 public:
  WorkerContextManager();
  virtual ~WorkerContextManager();

  int WorkerSize();

  std::shared_ptr<WorkerContext> Get(int fd);
  std::shared_ptr<WorkerContext> Get(const std::string&);
  bool Add(std::shared_ptr<WorkerContext> worker);
  void Del(std::shared_ptr<WorkerContext> worker);

  int IdleWorkerSize();
  std::shared_ptr<WorkerContext> FrontIdleWorker();
  void PopFrontIdleWorker();
  void PushBackIdleWorker(std::shared_ptr<WorkerContext> worker);

  void PushWaitWorker(std::shared_ptr<WorkerContext> worker);
  void WeakupWorker();

  void DispatchWorkerMsg(std::shared_ptr<Msg> msg);

 private:
  /// 工作线程数(包含用户线程)
  std::atomic_int cur_worker_count_ = {0};
  /// 读写锁
  pthread_rwlock_t rw_;
  /// 空闲线程链表
  std::list<std::weak_ptr<WorkerContext>> idle_workers_ctx_;
  /// 有消息user线程
  std::list<std::weak_ptr<WorkerContext>> weakup_workers_ctx_;
  /// name/handle 映射表
  std::unordered_map<std::string, int> name_handle_map_;
  /// handle/worker 映射表
  std::unordered_map<int, std::shared_ptr<WorkerContext>> worker_ctxs_;

  DISALLOW_COPY_AND_ASSIGN(WorkerContextManager)
};

}  // namespace myframe