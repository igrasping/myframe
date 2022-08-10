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
