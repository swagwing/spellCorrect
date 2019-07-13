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
    static Timer* createTimer();
    static void destroy();
    Timer* initTime(int initTime,int intervalTime,TimerCallback&& cb);
	void start();
	void stop();
	void setTimer(int initTime, int intervalTime);
    int getFd();
    void handleRead(); //包含读描述符和执行回写事件
private:
    Timer() {}
    ~Timer() {}
	int createTimerfd();
private:
    static Timer* _pTimer;
	int _fd;
	int _initalTime;
	int _intervalTime;
	TimerCallback _cb;
	bool _isStarted;
};

}
             
 

#endif
