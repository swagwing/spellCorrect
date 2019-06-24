#ifndef __WD_INDEXPRODUCER_H__
#define __WD_INDEXPRODUCER_H__
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <set>
#include <vector>

using namespace std;

namespace wd
{

class IndexProducer
{
public:
    explicit IndexProducer(vector<pair<string,int>> &);
    
    //创建索引
    void build_index();

    //将索引写入文件
    void store_index(const char*);
private:
    vector<pair<string,int>> _dict;
    map<string,set<int>> _indexMap;
    int _cnt;
};

}//end od namespace wd

#endif
