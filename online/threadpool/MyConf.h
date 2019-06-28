#ifndef __WD_MYCONF_H__
#define __WD_MYCONF_H__
#include <iostream>
#include <map>
#include <fstream>
using namespace std;

namespace wd
{

class MyConf
{
public:
    MyConf(const string& filepath);
    map<string,string>& getConfigMap();
private:
    string _filepath;
    map<string,string> _configMap;
};

}//end of namespace wd

#endif

