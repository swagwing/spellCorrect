#include "Cache.h"

namespace wd
{

Cache::Cache()
{}

void Cache::addElement(const string& key ,const string& value)
{
    _updateData.push_back(make_pair(key,value));
}

void Cache::readFromFile(const string& fileName)
{
    ifstream ifs(fileName);
    string str1,str2;
    while(ifs >> str1 >> str2){
        _hashMap.insert(make_pair(str1,str2));
    }
}

void Cache::writeToFile(const string& fileName)
{
    ofstream ofs(fileName);
    auto it = _hashMap.begin();
    while(it != _hashMap.end()){
        ofs << it->first << " " << it->second << endl;
        ++it;
    }
}

//void Cache::update(const Cache& rhs)
//{
//    string str1,str2;
//    auto it = _updateData.begin();
//    while(it !=_updateData.end()){
//        str1 = it->first;
//        str2 = it->second;
//        _hashMap.insert(make_pair(str1,str2));
//        ++it;
//    }
//}

string Cache::search(const string& word)
{
    auto it = _hashMap.find(word);
    if(it != _hashMap.end()){
        return it->second;
    }
    else
        return string();
}

list<pair<string,string>> Cache::getHotData()
{
    return _updateData;
}

}//end of namespace wd
