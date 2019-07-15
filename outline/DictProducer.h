#ifndef __WD_DICTPRODUCER_H__
#define __WD_DICTPRODUCER_H__
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include "Configuration.h"
#define MAXSIZE 50

using namespace std;

namespace wd
{

class DictProducer
{
public:
    DictProducer(map<string,string>);
    void build_dict(); //创建英文字典
    void build_cn_dict();//创建中文字典
    void store_dict(const char*); //将词典写入文件
private:
    map<string,string> _configMap;
    string _dir; //英文语料库存放位置
    vector<string> _cnPath; //中文语料库存储位置
    map<string,int> _dict; //存放词典
};

}//end of namespace wd

#endif
