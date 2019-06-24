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
    set<int> current;
    while(ifs >> alpha){
        int pos;
        while(ifs >> pos){
            current.insert(pos);
        }
        _index_table.insert({alpha,current});
    }
    return _index_table;
}

MyDict* MyDict::_pInstance = nullptr;

}//end of namespace wd

