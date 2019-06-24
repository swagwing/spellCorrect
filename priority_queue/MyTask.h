#ifndef __WD_MYTASK_H_
#define __WD_MYTASK_H_
#include <queue>
#include <iostream>
#include <set>
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
        return a._iDict < b._iDict;
    }
};

class MyTask
{
public:
    MyTask(const string&);
    void queryIndexTable();
    void statistic(set<int>&);
    int distance(const string&);
private:
    string _queryWord; //等查询的单词
    priority_queue<MyResult,vector<MyResult>,MyCompare> _resultQue; //保存候选词的优先级队列
};
}//end of namespace wd

#endif
