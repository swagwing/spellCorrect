#include "Configuration.h"

namespace wd
{

Configuration::Configuration(const string& filepath)
    :_filepath(filepath)
{}

vector<pair<string,int>> & Configuration::getConfigMap()
{
    ifstream ifs(_filepath);
    string word;
    int frequency;
    while(ifs >> word >> frequency){
        _configMap.push_back(make_pair(word,frequency));
    }
    return _configMap;
}

}//end of namespace wd
