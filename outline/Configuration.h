#ifndef __WD_CONFIGURATION_H__
#define __WD_CONFIGURATION_H__
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

namespace wd
{

class Configuration
{
public:
    explicit Configuration(const string&);
    vector<pair<string,int>> & getConfigMap();
private:
    string _filepath; //配置文件路径
    vector<pair<string,int>> _configMap; //配置文件内容
};

}//end of namespace wd

#endif
