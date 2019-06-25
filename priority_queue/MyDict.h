#ifndef __WD_MYDICT_H__
#define __WD_MYDICT_H__
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <fstream>
#include <sstream>
using namespace std;

namespace wd
{

class MyDict
{
public:
    static MyDict* createInstance(); //静态函数
    void init(const char*); //通过英文路径初始化词典
    vector<pair<string,int>>& getDict(); //获取词典
    map<string,set<int>>& getIndexTable(const char*); //获取索引表

private:
    MyDict() {}

private:
    static MyDict* _pInstance;
    vector<pair<string,int>> _dict; //词典
    map<string,set<int>> _index_table; //索引表
};

}//end of namespace wd

#endif
