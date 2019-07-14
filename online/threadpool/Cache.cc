#include "Cache.h"

namespace wd
{

Cache::Cache()
{}

void Cache::addElement(const string& key ,const string& value)
{ 
    _updateData.push_front(make_pair(key,value));
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
    return _updateData;
}

}//end of namespace wd
