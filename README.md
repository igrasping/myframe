# myframe

[![Build Status](https://travis-ci.com/lkpworkspace/myframe.svg?branch=master)](https://travis-ci.com/lkpworkspace/myframe)
[![cpp](https://img.shields.io/badge/language-cpp-green.svg)](https://img.shields.io/badge/language-cpp-green.svg)

## 概述
C++实现的actors框架,框架中每一个actor都可以称为一个服务或者是一个组件(这里都称为服务)，你可以将每一个独立的业务逻辑都编写成一个服务,服务基于消息驱动,服务之间可以进行消息传递，这样一个大型的应用程序或服务器程序就可以由多个服务组成，不同服务组合使用，既可以提高代码复用，又可以极大的降低程序耦合度，提高开发效率。
- 服务(service): 线程池执行单位
    - service之间可以相互传递消息，线程池可以高并发的处理收到消息的服务；
- 工作者(worker): 独立线程
    - worker可以发送消息给service。

## 安装依赖
## 构建

```sh
mkdir build
cd build
cmake ..
sudo make install
```

## 运行

```sh
sudo bash /opt/myframe/bin/start_myframe.bash
```

## 创建模块工程
```sh
python3 /opt/myframe/tools/gen_mod_proj.py --dir="/path/to/proj_dir/" --name="mod_name"
```

### 服务 Hello,World Demo 示例

```c
#include <iostream>
#include <string.h>

#include "myframe/MyActor.h"
#include "myframe/MyMsg.h"

/*
    该服务实现：
        自己给自己发送一条消息
*/
class MyDemo : public MyActor
{
public:
    /* 服务模块加载完毕后调用 */
    int Init(const char* param) override {
        /* 构造 hello,world 消息发送给自己 */
        return Send("demo.echo_hello_world", std::make_shared<MyTextMsg>("hello,world"));
    }

    void CB(std::shared_ptr<MyMsg>& msg) override {
        if (msg->GetMsgType() == "TEXT") {
            /* 获得文本消息， 打印 源服务地址 目的服务地址 消息内容*/
            auto tmsg = std::dynamic_pointer_cast<MyTextMsg>(msg);
            std::cout << "----> from \"" << tmsg->GetSrc() << "\" to \"" 
                << GetServiceName() << "\": " << tmsg->GetData() << std::endl;
        }
    }
};

/* 创建服务模块实例函数 */
extern "C" std::shared_ptr<MyActor> my_actor_create(const std::string& service_name) {
    return std::make_shared<MyDemo>();
}

```

### 服务配置文件
```json
{
    "type":"library",
    "lib":"libdemo.so",
    "service":{
        "demo":[
            {
                "instance_name":"echo_hello_world",
                "instance_params":""
            }
        ]
    }
}
```
- type: [ library | class ]
- lib: 库名称
- service: 需要创建的服务列表
    - demo: 服务名
        - instance_name：实例名称
        - instance_params：实例参数

## 程序接口

- [服务模块](https://github.com/lkpworkspace/myframe/blob/master/myframe/MyModule.h)

- [消息类型](https://github.com/lkpworkspace/myframe/blob/master/myframe/MyMsg.h)

## 文档
- [文档入口](https://github.com/lkpworkspace/myframe/wiki)

## 常见问题
- [FAQs](https://github.com/lkpworkspace/myframe/wiki/FAQs)

### TODOLIST
- 减少继承
    - context不继承MyNode
- 全部使用智能指针
    - 解决addevent(MyEvent*)
- 提供完整应用程序的demo示例图