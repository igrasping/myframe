/****************************************************************************
Copyright (c) 2019, 李柯鹏
All rights reserved.

Author: 李柯鹏 <likepeng0418@163.com>
****************************************************************************/
#pragma once
#include <string>
#include <list>
#include "cmdline.h"

namespace myframe {

class ModuleArgument final {
 public:
  ModuleArgument(const std::string& sys_conf_dir);
  ~ModuleArgument() = default;

  void ParseArgument(const int argc, char** argv);
  inline std::list<std::string> GetConfList() const { return conf_list_; }
  inline std::string GetConfDir() const { return conf_dir_; }
  inline std::string GetBinaryName() const { return binary_name_; }
  inline std::string GetProcessName() const { return process_name_; }
  inline std::string GetCmd() const { return cmd_; }
  inline int GetThreadPoolSize() const { return thread_poll_size_; }
  inline int GetConnEventSize() const { return conn_event_size_; }
  inline int GetWarningMsgSize() const { return warning_msg_size_; }

 private:
  bool ParseSysConf(const std::string&);

  int thread_poll_size_{4};
  int conn_event_size_{2};
  int warning_msg_size_{10};
  std::string cmd_{""};
  std::string binary_name_{""};
  std::string process_name_{""};
  std::string conf_dir_{""};
  std::string sys_conf_dir_{"conf"};
  std::list<std::string> conf_list_;
  cmdline::parser parser_;
};

}  // namespace myframe
