#ifndef __WD_CONFIGURATION_H__
#define __WD_CONFIGURATION_H__
#include <iostream>
#include <string>
#include <fstream>
#include <map>
using namespace std;

namespace wd
{

class Configuration
{
public:
    explicit Configuration(const string&);
    map<string,string> & getConfigMap();
private:
    string _filepath; //配置文件路径
    map<string,string> _configMap; //配置文件内容
};

}//end of namespace wd

#endif
