#ifndef __WD_DICTPRODUCER_H__
#define __WD_DICTPRODUCER_H__
#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#define MAXSIZE 50
using namespace std;

namespace wd
{

class DictProducer
{
public:
    DictProducer(const string&);

    //创建英文词典
    void build_dict();

    //将词典写入文件
    void store_dict(const char*);
private:
    string _dir; //语料库存放位置
    map<string,int> _dict; //存放词典
};

}//end of namespace wd

#endif
