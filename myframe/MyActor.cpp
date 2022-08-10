#include "MyActor.h"
#include "MyContext.h"
#include "MyWorkerTimer.h"
#include "MyApp.h"

MyActor::MyActor() : 
    m_ctx(nullptr) {
}

MyActor::~MyActor()
{}

int MyActor::Send(const std::string& dst, std::shared_ptr<MyMsg> msg) {
    msg->SetSrc(GetServiceName());
    msg->SetDst(dst);
    return m_ctx->SendMsg(msg);
}

uint32_t MyActor::GetHandle() {
    return m_ctx->GetHandle();
}

std::string MyActor::GetServiceName() {
    return m_service_name + "." + m_instance_name;
}

int MyActor::Timeout(int time) {
    return MyApp::Inst()->GetTimerWorker()->SetTimeout(GetServiceName(), time);
}

void MyActor::SetContext(MyContext* c) {
    m_ctx = c;
}