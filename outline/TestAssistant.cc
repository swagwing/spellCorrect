#include "DictProducer.h"
#include "Configuration.h"
#include "IndexProducer.h"

int main()
{
    string filename = "english.txt";
    wd::DictProducer test(filename);
    test.build_dict();
    test.store_dict("dict");
    string dict_name = "dict";
    wd::Configuration conf(dict_name);
    vector<pair<string,int>> config_dict;
    config_dict = conf.getConfigMap();
    wd::IndexProducer indexMap(config_dict);
    indexMap.build_index();
    indexMap.store_index("./index");
    return 0;
}

