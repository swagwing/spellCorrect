#ifndef __WD_CACHE_H__
#define __WD_CACHE_H__
#include <iostream>
#include <unordered_map>
#include <list>
#include <fstream>
using namespace std;

namespace wd
{

class Cache
{
public:
    Cache();
    void addElement(const string&, const string&); //往缓存中添加信息
    void readFromFile(const string&); //从文件中读取缓存文件
    void writeToFile(const string&); //将缓存信息写入到文件中
    void update(const Cache&); //更新缓存信息
private:
    unordered_map<string,string> _hashMap;
    list<pair<string,string>> _updateData;
};

}//end of namespace wd

#endif
