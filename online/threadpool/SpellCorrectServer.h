#ifndef __WD_SPELLCORRECTSERVER_H__
#define __WD_SPELLCORRECTSERVER_H__
#include "TcpServer.h"
#include "Threadpool.h"
#include "MyConf.h"
#include "MyDict.h"
#include "MyTask.h"
#include "TimerThread.h"
#include "CacheManager.h"
#include <iostream>
#include <functional>
using namespace std;

namespace wd
{

class SpellCorrectServer
{
public:
    explicit SpellCorrectServer(const string&);
    void start(); //开始提供服务
    void onConnection(const TcpConnectionPtr&); //被注册回调函数，提供给TcpServer使用
    void onMessage(const TcpConnectionPtr&);
    void onClose(const TcpConnectionPtr&);
private:
    MyConf _conf;
    TcpServer _tcpserver;
    Threadpool _threadpool;
    CacheManager* _pCacheM;
    TimerThread _timerThread;

};

}//end of namespace wd

#endif
