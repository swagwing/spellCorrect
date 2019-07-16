#include "DictProducer.h"
#include "Configuration.h"
#include "IndexProducer.h"

int main()
{
    string filename = "./config";
    wd::Configuration conf(filename);
    map<string,string> configMap = conf.getConfigMap();
    wd::DictProducer test(configMap);
    test.build_dict();
    test.build_cn_dict();
    test.store_dict("dict");
    string dict_name = "dict";
    wd::IndexProducer indexMap(dict_name);
    indexMap.build_index();
    indexMap.store_index("./index");
    return 0;
}

