#include "CacheManager.h"

namespace wd
{

CacheManager* CacheManager::createInstance()
{
    if(_pCacheManager == nullptr){
        _pCacheManager = new CacheManager();
    }
    return _pCacheManager;
}

CacheManager* CacheManager::initCache(size_t capacity,const string& fileName)
{
    Cache cache;
    cache.readFromFile(fileName);
    for (size_t i=0; i<capacity; ++i){
        _cacheList.push_back(cache);
    }
    return _pCacheManager;
}

Cache& CacheManager::getCache(size_t num)
{
    return _cacheList[num-1];
}

void CacheManager::periodicUpdateCaches()
{
    size_t num = _cacheList.capacity();
    for(size_t i = 0; i<num; ++i){
        _cacheList[i].update(_cacheList[i]);
    }
    MyConf conf("../conf/config"); //总感觉不太对
    _cacheList[0].writeToFile(conf.getConfigMap().find("cachePath")->second);
}

CacheManager* CacheManager::_pCacheManager = nullptr;

}//end of namespace wd
