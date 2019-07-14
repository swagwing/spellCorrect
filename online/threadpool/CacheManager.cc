#include "CacheManager.h"

namespace wd
{

CacheManager::CacheManager()
{
    cout << "CacheManager()" << endl;
}

CacheManager* CacheManager::createInstance()
{
    if(_pCacheManager == nullptr){
        _pCacheManager = new CacheManager();
        atexit(destroy);
    }
    return _pCacheManager;
}

void CacheManager::destroy()
{
    if(_pCacheManager)
        delete _pCacheManager;
}

CacheManager* CacheManager::initCache(size_t capacity)
{
    Cache cache;
    for (size_t i=0; i<capacity; ++i){
        _cacheList.push_back(cache);
    }
    MyConf conf("../conf/config"); //￥￥￥硬编码，待修改
    CacheManager::readFromFile(conf.getConfigMap().find("cachePath")->second);
    return _pCacheManager;
}

Cache& CacheManager::getCache(size_t num)
{
    return _cacheList[num-1];
}

void CacheManager::periodicUpdateCaches()
{
    cout << "####enter CacheManager::periodicUpdateCaches" << endl;
    list<pair<string,string>> iUpdateData;
    string str1,str2;
    size_t num = _cacheList.capacity();
    for(size_t i = 0; i<num; ++i){
        iUpdateData = _cacheList[i].getHotData();
        auto it = iUpdateData.begin();
        while(it != iUpdateData.end()){
            str1 = it->first;
            str2 = it->second;
            _hashMap.insert(make_pair(str1,str2));
            ++it;
        }
    }
    MyConf conf("../conf/config"); //$$$硬编码，待修改
    CacheManager::writeToFile(conf.getConfigMap().find("cachePath")->second);
}
void CacheManager::readFromFile(const string& fileName)
{
    cout << "enter CacheManager::readFromFile" << endl;
    ifstream ifs(fileName);
    string str1,str2;
    while(ifs >> str1 >> str2){
        _hashMap.insert(make_pair(str1,str2));
    }
    cout << "CacheManager::readFromFile-->_hashMap" << endl; //***以下皆为测试信息
    auto it = _hashMap.begin();
    while(it != _hashMap.end()){
        cout << it->first << " " << it->second << endl;
        ++it;
    }
}

void CacheManager::writeToFile(const string& fileName)
{
    ofstream ofs(fileName);
    auto it = _hashMap.begin();
   while(it != _hashMap.end()){
        ofs << it->first << " " << it->second << endl;
        ++it;
    }
}

string CacheManager::searchMainCache(string& word)
{
    auto it = _hashMap.find(word);
    if(it != _hashMap.end())
        return it->second;
    else 
        return string();
}

CacheManager* CacheManager::_pCacheManager = nullptr;

}//end of namespace wd
