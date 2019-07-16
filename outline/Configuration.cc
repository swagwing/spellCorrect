#include "Configuration.h"

namespace wd
{

Configuration::Configuration(const string& filepath)
    :_filepath(filepath)
{}

map<string,string>& Configuration::getConfigMap()
{
    ifstream ifs(_filepath);
    string name,path;
    while(ifs >> name >> path){
        _configMap.insert(make_pair(name,path));
    }
    return _configMap;
}

}//end of namespace wd
