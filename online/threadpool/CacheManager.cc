#include "CacheManager.h"
#include "Cache.h"

namespace wd
{

void CacheManager::initCache(size_t capacity,const string& fileName)
{
    Cache cache;
    cache.readFromFile(fileName);
    for (size_t i=0; i<capacity; ++i){
        _cacheList.push_back(cache);
    } 
}

Cache& CacheManager::getCache(size_t num)
{
    return _cacheList[num];
}

void CacheManager::periodicUpdateCaches()
{
    size_t num = _cacheList.capacity();
    for(size_t i = 0; i<num; ++i){
        _cacheList[i].update(_cacheList[i]);
    }
}

}//end of namespace wd
