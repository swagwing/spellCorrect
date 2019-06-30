#ifndef __WD_CACHEMANAGER_H__
#define __WD_CACHEMANAGER_H__
#include "Cache.h"
#include <vector>
#include <iostream>
using namespace std;

namespace wd
{

class CacheManager
{
private:
    static vector<Cache> _cacheList; 
public:
    static void initCache(size_t,const string&); //从磁盘文件中读取缓存信息
    static Cache& getCache(size_t); //获取某个缓存
    static void periodicUpdateCaches(); //定时更新所有的缓存
};
}//end of namespace wd

#endif
