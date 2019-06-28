#include "MyConf.h"

namespace wd
{

MyConf::MyConf(const string& filepath)
    :_filepath(filepath)
{}

map<string,string>& MyConf::getConfigMap()
{
    ifstream ifs(_filepath);
    string str1,str2;
    while(ifs >> str1 >> str2){
        _configMap.insert(make_pair(str1,str2));
    }
    return _configMap;
}

}//end of namespace wd
