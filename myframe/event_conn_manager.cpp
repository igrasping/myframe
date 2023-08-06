/****************************************************************************
Copyright (c) 2018, likepeng
All rights reserved.

Author: likepeng <likepeng0418@163.com>
****************************************************************************/

#include "myframe/event_conn_manager.h"

#include <glog/logging.h>

#include "myframe/event_conn.h"
#include "myframe/event_manager.h"

namespace myframe {

EventConnManager::EventConnManager(std::shared_ptr<EventManager> ev_mgr)
  : ev_mgr_(ev_mgr) {
  LOG(INFO) << "EventConnManager create";
}

EventConnManager::~EventConnManager() {
  LOG(INFO) << "EventConnManager deconstruct";
}

bool EventConnManager::Init(int sz) {
  for (int i = 0; i < sz; ++i) {
    std::lock_guard<std::mutex> g(mtx_);
    AddEventConn();
  }
  return true;
}

void EventConnManager::AddEventConn() {
  auto conn = std::make_shared<EventConn>();
  std::string name = "event.conn." + std::to_string(conn_sz_);
  conn->GetMailbox()->SetAddr(name);
  idle_conn_.emplace_back(conn);
  conn_sz_++;
}

std::shared_ptr<EventConn> EventConnManager::Alloc() {
  std::lock_guard<std::mutex> g(mtx_);
  // check has event conn
  if (idle_conn_.empty()) {
    AddEventConn();
  }
  // remove from idle_conn
  auto conn = idle_conn_.front();
  idle_conn_.pop_front();
  // add to run_conn
  if (!ev_mgr_->Add(conn)) {
    return nullptr;
  }
  return conn;
}

void EventConnManager::Release(std::shared_ptr<EventConn> ev) {
  // remove from run_conn
  ev_mgr_->Del(ev);
  // add to idle_conn
  std::lock_guard<std::mutex> g(mtx_);
  idle_conn_.emplace_back(ev);
}

// call by main frame
void EventConnManager::Notify(
  ev_handle_t h,
  std::shared_ptr<Msg> msg) {
  std::shared_ptr<EventConn> ev = nullptr;
  ev = ev_mgr_->Get<EventConn>(h);
  if (ev == nullptr) {
    LOG(ERROR) << "can't find handle " << h;
    return;
  }
  if (ev->GetConnType() == EventConn::Type::kSend) {
    LOG(WARNING) << "event " << ev->GetName() << " need't resp msg";
    return;
  }
  // push msg to event_conn
  ev->GetMailbox()->Recv(msg);
  // send cmd to event_conn
  auto cmd_channel = ev->GetCmdChannel();
  cmd_channel->SendToOwner(CmdChannel::Cmd::kIdle);
}

}  // namespace myframe
