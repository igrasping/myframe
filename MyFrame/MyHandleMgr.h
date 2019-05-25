#ifndef __MYHANDLEMGR_H__
#define __MYHANDLEMGR_H__
#include <stdint.h>
#include "MyCommon.h"

#define MY_HANDLE_MASK 0xffffff
#define MY_HANDLE_REMOTE_SHIFT 24

struct MyHandle
{
    char* name;
    uint32_t handle;
};

class MyContext;
class MyHandleMgr
{
public:
    MyHandleMgr();
    virtual ~MyHandleMgr();

    /* 给服务分配句柄，并进行管理 */
    uint32_t RegHandle(MyContext* ctx);
    /* 获得句柄对应的服务 */
    MyContext* GetContext(uint32_t handle);
    /* 获得下一个服务 */
    MyContext* GetNextContext();
private:
    uint32_t            m_harbor;         // 暂时没用

    int                 m_slot_size;      // 当前服务数组大小

    uint32_t            m_slot_idx;       // 当前要处理消息的服务下标

    MyContext**         m_slot;           // 服务数组

    uint32_t            m_ctx_count;      // 当前注册服务数量

    uint32_t            m_handle_index;   // 分配的句柄
};

#endif
