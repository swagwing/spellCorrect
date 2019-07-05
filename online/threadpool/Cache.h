#ifndef __WD_CACHE_H__
#define __WD_CACHE_H__
#include <iostream>
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
    string search(const string&); //在内存中查询候选词
    list<pair<string,string>> getHotData();//获取热数据列表
private:
    list<pair<string,string>> _updateData;
};

}//end of namespace wd

#endif
