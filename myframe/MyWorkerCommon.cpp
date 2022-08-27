#include "MyWorkerCommon.h"
#include "MyLog.h"
#include "MyContext.h"
#include "MyMsg.h"

MyWorkerCommon::MyWorkerCommon() :
    _context(nullptr) {
}

MyWorkerCommon::~MyWorkerCommon() {
}

void MyWorkerCommon::Idle() {
    if(_context){
        _context->SetWaitFlag();
        _context = nullptr;
    }
}

void MyWorkerCommon::Run() {
    DispatchMsg();
    Work();
}

void MyWorkerCommon::OnInit() {
    MyWorker::OnInit();
    LOG(INFO) << "Worker " << GetInstName() << " init";
}

void MyWorkerCommon::OnExit() {
    MyWorker::OnExit();
    LOG(INFO) << "Worker " << GetInstName() << " exit";
}

int MyWorkerCommon::Work() {
    MyContext* ctx = _context;
    if (ctx == nullptr) {
        LOG(ERROR) << "context is nullptr";
        return -1;
    }
    while (RecvMsgListSize() > 0) {
        ctx->CB(GetRecvMsg());
    }
    
    return 0;
}
