#include "Thread.h"
#include <iostream>
using namespace std;

namespace wd
{
__thread int threadNum = 0;
using ThreadCallback = std::function<void()>;
struct ThreadData
{
    int Num_;
    ThreadCallback cb_;
    ThreadData(const int Num,ThreadCallback cb)
        :Num_(Num)
         ,cb_(cb)
    {}
    void runInThread()
    {
        threadNum = Num_;
        cout << "thread " << threadNum << ": Thread()" << endl;
        if(cb_)
            cb_();
    }
};

Thread::Thread(ThreadCallback && cb,int num)
    : _pthid(0)
    , _cb(std::move(cb))
    , _isRunning(false)
      ,_threadNumber(num)
{}

void Thread::start()
{
    ThreadData* data = new ThreadData(_threadNumber,_cb);
    pthread_create(&_pthid, NULL, threadFunc, data);	
    _isRunning = true;
}

void * Thread::threadFunc(void * arg)
{
    ThreadData * pthread = static_cast<ThreadData*>(arg);
    if(pthread)
        pthread->runInThread();
    delete pthread;
    return nullptr;
}

void Thread::join()
{
    if(_isRunning)
        pthread_join(_pthid, NULL);
}

Thread::~Thread()
{
    if(_isRunning) {
        pthread_detach(_pthid);	
    }
    cout << "thread " << threadNum << ": ~Thread()" << endl;
}

}//end of namespace wd
