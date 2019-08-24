#ifndef __MYFRAME_H__
#define __MYFRAME_H__

#include <cstddef>
#include <cstdint>

/* 系统的句柄号 */
#define MY_FRAME_DST 0xffffff

class MyMsg;
class MyContext;

/**
 * my_send() - 发送消息
 * @ctx:            服务指针
 * @msg:            发送的消息
 * 
 * @return:         成功 0， 失败 -1
 */
int my_send(MyContext* ctx, MyMsg* msg);

uint32_t my_handle(MyContext* ctx);

int my_timeout(uint32_t handle, int time, int session);

MyContext* my_context(uint32_t handle);

typedef int (*my_cb)(MyContext* context, MyMsg* msg, void* ud);
void my_callback(MyContext* ctx, my_cb cb, void* ud);

int my_listen(MyContext* ctx, const char* addr, int port, int backlog);
int my_sock_send(uint32_t id, const void* buf, int sz);

#endif // __MYFRAME_H__
