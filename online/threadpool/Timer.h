 ///
 /// @file    Timer.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-06-14 10:12:57
 ///
 
#ifndef __WD_TIMER_H__
#define __WD_TIMER_H__


#include <functional>
using namespace std;

namespace wd
{

class Timer
{
	using TimerCallback = function<void()>;
public:
	Timer(int initTime, int intervalTime, TimerCallback && cb)
	: _fd(createTimerfd())
	, _initalTime(initTime)
	, _intervalTime(intervalTime)
	, _cb(move(cb))
	, _isStarted(false)
	{}

	void start();
	void stop();
	void setTimer(int initTime, int intervalTime);
    int getFd();
private:
	int createTimerfd();
	void handleRead();

private:
	int _fd;
	int _initalTime;
	int _intervalTime;
	TimerCallback _cb;
	bool _isStarted;
};

}
             
 

#endif
