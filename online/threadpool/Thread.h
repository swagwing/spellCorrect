#ifndef __WD_THREAD_H__
#define __WD_THREAD_H__
#include "Noncopyable.h"

#include <pthread.h>
#include <functional>

namespace wd
{

extern __thread int threadNum;
class Thread
    : Noncopyable
{
public:
    using ThreadCallback = std::function<void()>;
    Thread(ThreadCallback&&,int);

    void start();
    void join();

    ~Thread();

private:
    static void * threadFunc(void *);

private:
    pthread_t _pthid;
    ThreadCallback _cb;
    bool _isRunning;
    int _threadNumber;
};

}//end of namespace wd

#endif
