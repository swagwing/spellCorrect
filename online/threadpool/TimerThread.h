 ///
 /// @file    TimerThread.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-06-14 11:21:27
 ///
 
#include "Timer.h"
#include "Thread.h"
#include <iostream>
using namespace std;
             
namespace wd
{
class TimerThread
{
	using TimerCallback = function<void()>;
public:
	TimerThread(int initTime, int intervalTime,  TimerCallback && cb)
	: _timer(initTime, intervalTime, move(cb))
	, _thread(bind(&Timer::start, &_timer),-1)
	{}

	void start()
	{
        cout << "TimerThread.h--->start()" << endl;
		_thread.start();
	}

	void stop()
	{
		_timer.stop();
		_thread.join();
	}

private:
	Timer _timer;
	Thread _thread;
};
}//end of namespace wd
 
