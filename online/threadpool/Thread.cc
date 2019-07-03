#include "Thread.h"
#include <iostream>
using namespace std;

namespace wd
{
__thread int threadNum = 0;

Thread::Thread(ThreadCallback && cb,int num)
: _pthid(0)
, _cb(std::move(cb))
, _isRunning(false)
,_threadNumber(num)
{
    threadNum = _threadNumber;
	cout << "thread " << threadNum << ": Thread()" << endl;
}

void Thread::start()
{
	pthread_create(&_pthid, NULL, threadFunc, this);	
	_isRunning = true;
}

void * Thread::threadFunc(void * arg)
{
	Thread * pthread = static_cast<Thread*>(arg);
	if(pthread)
		pthread->_cb();

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
