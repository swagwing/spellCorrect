#ifndef __WD_CACHEMANAGER_H__
#define __WD_CACHEMANAGER_H__
#include "Cache.h"
#include "MyConf.h"
#include <vector>
#include <unordered_map>
#include <iostream>
using namespace std;

namespace wd
{

class CacheManager
{
public:
    static CacheManager* createInstance();
    CacheManager* initCache(size_t); //从磁盘文件中读取缓存信息
    void readFromFile(const string&);
    void writeToFile(const string&);
    Cache& getCache(size_t); //获取某个缓存
    void periodicUpdateCaches(); //定时更新所有的缓存
    string searchMainCache(string& word);
private:
    CacheManager();
private:
    static CacheManager* _pCacheManager;
    vector<Cache> _cacheList;
    unordered_map<string,string> _hashMap; 
};
}//end of namespace wd

#endif
