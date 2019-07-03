#ifndef __WD_MYTASK_H_
#define __WD_MYTASK_H_
#include "MyDict.h"
#include "TcpServer.h"
#include "CacheManager.h"
#include "Cache.h"
#include "Thread.h"
#include <queue>
#include <iostream>
#include <set>
#include <json/json.h>
#define INF 0x3f3f3f3f
using namespace std;

namespace wd
{

struct MyResult
{
    string _word; //候选词
    int _iFreq; //词频
    int _iDict; //与查询词的最小编辑距离
};

struct MyCompare
{
    bool operator() (MyResult a,MyResult b){
        if(a._iDict == b._iDict && a._iFreq == b._iFreq)
            return a._word < b._word;
        if(a._iDict == b._iDict)
            return a._iFreq > b._iFreq;
        return a._iDict > b._iDict;
    }
};

class MyTask
{
public:
    MyTask(const string&,const wd::TcpConnectionPtr&,MyDict*,CacheManager*);
    void execute(); //执行cache查询
    void queryIndexTable();
    void statistic(set<int>&);
    int distance(const string&);
    void response();
private:
    TcpConnectionPtr _conn;
    string _queryWord; //等查询的单词
    MyDict* _pInstance;
    CacheManager* _pCacheM;
    priority_queue<MyResult,vector<MyResult>,MyCompare> _resultQue; //保存候选词的优先级队列
};
}//end of namespace wd

#endif
