#include "Cache.h"

namespace wd
{

Cache::Cache()
{}

void Cache::addElement(const string& key ,const string& value)
{
    _updateData.push_front(make_pair(key,value));
    cout << "Cache::addElement-->_updateData" << endl; //**以下均为测试信息
    auto it = _updateData.begin();
    while(it != _updateData.end()){
        cout << it->first << " " <<it->second << endl;
        ++it;
    }
}

string Cache::search(const string& word)
{
    auto it = _updateData.begin();
    while(it != _updateData.end()){
        if(word == it->first){
            return it->second;
        }
        ++it;
    }
    return string();
}

list<pair<string,string>> Cache::getHotData()
{
    cout << "Cache::getHotData-->_updateData" << endl; //***测试信息
    auto it = _updateData.begin();
    while(it != _updateData.end()){
        cout << it->first << " " <<it->second << endl;
        ++it;
    }
    return _updateData;
}

}//end of namespace wd
