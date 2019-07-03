#ifndef __WD_CACHEMANAGER_H__
#define __WD_CACHEMANAGER_H__
#include "Cache.h"
#include "TimerThread.h"
#include "MyConf.h"
#include <vector>
#include <iostream>
using namespace std;

namespace wd
{

class CacheManager
{
public:
    static CacheManager* createInstance();
    static CacheManager* initCache(size_t,const string&); //从磁盘文件中读取缓存信息
    static Cache& getCache(size_t); //获取某个缓存
    void periodicUpdateCaches(); //定时更新所有的缓存
private:
    CacheManager() {}
private:
    static CacheManager* _pCacheManager;
    static vector<Cache> _cacheList; 
};
}//end of namespace wd

#endif
