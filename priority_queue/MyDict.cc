#include "MyDict.h"

namespace wd
{

MyDict* MyDict::createInstance()
{
    if(_pInstance == nullptr){
        _pInstance = new MyDict();
    }
    return _pInstance;
};

void MyDict::init(const char* dictEnPath)
{
    ifstream ifs(dictEnPath);
    string word;
    int frequency;
    while(ifs >> word >> frequency){
        _dict.push_back(make_pair(word,frequency));
    }
}

vector<pair<string,int>>& MyDict::getDict()
{
    return _dict;
}

map<string,set<int>>& MyDict::getIndexTable(const char* indexPath)
{
    ifstream ifs(indexPath);
    string alpha;
    string line;
    int pos;
    int cnt = 1;
    while(getline(ifs,line))
    {
        stringstream ss(line);
        if(cnt%2 != 0)
            ss >> alpha;
        else{
            while(ss >> pos){
                _index_table[alpha].insert(pos);
            }
        }
        ++cnt;
    }
    return _index_table;
}

MyDict* MyDict::_pInstance = nullptr;

}//end of namespace wd

