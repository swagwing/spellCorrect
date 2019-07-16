#include "DictProducer.h"
#include "../include/cppjieba/include/cppjieba/Jieba.hpp"
namespace wd
{
const char* const DICT_PATH = "../include/cppjieba/dict/jieba.dict.utf8";
const char* const HMM_PATH = "../include/cppjieba/dict/hmm_model.utf8";
const char* const USER_DICT_PATH = "../include/cppjieba/dict/user.dict.utf8";
const char* const IDF_PATH = "../include/cppjieba/dict/idf.utf8";
const char* const STOP_WORD_PATH = "../include/cppjieba/dict/stop_words.utf8";

#if 0
bool cmp(const pair<string,int> &lhs,const pair<string,int> &rhs)
{
    return lhs.second > rhs.second;
}
#endif

void mytolower(string& s)
{
    int len = s.length();
    for(int i=0; i<len; ++i){
        if(s[i] >= 'A' && s[i] <= 'Z'){
            s[i] += 32;
        }
    }
}

bool is_chinese(const string& str)
{
    unsigned char utf[4] = {0};
    unsigned char unicode[3] = {0};
    bool res = false;
    for (int i = 0; i < str.length(); i++) {
        if ((str[i] & 0x80) == 0) {   //ascii begin with 0
            res = false;
        }
        else /*if ((str[i] & 0x80) == 1) */{
            utf[0] = str[i];
            utf[1] = str[i + 1];
            utf[2] = str[i + 2];
            i++;
            i++;
            unicode[0] = ((utf[0] & 0x0F) << 4) | ((utf[1] & 0x3C) >>2);
            unicode[1] = ((utf[1] & 0x03) << 6) | (utf[2] & 0x3F);
            if(unicode[0] >= 0x4e && unicode[0] <= 0x9f){
                if (unicode[0] == 0x9f && unicode[1] >0xa5)
                    res = false;
                else         
                    res = true;
            }else
                res = false;
        }
    }
    return res;
}

DictProducer::DictProducer(map<string,string> map)
    :_configMap(map)
{
    _dir = _configMap.find("enPath")->second;
    auto it = _configMap.begin();
    while(it != _configMap.end()){
        if(it->first.compare(0,6,"cnPath")==0)
            _cnPath.push_back(it->second);
        ++it;
    }
}

//创建英文词典
void DictProducer::build_dict()
{
    ifstream ifs(_dir);
    string word;
    char word_real[MAXSIZE];
    while(ifs >> word){
        if(!isalpha(word[0]))
            continue;
        else{
            int len = word.length();
            int i = 0;
            int cnt = 0;
            while(i != len){
                if(!isalpha(word[i]))
                    break;
                else{
                    mytolower(word);
                    word_real[cnt] = word[i];
                    ++i;
                    ++cnt;
                }
            }
            word_real[cnt] = '\0';
            ++_dict[word_real];
        }
    }
}

//创建中文词典
void DictProducer::build_cn_dict()
{
    cppjieba::Jieba jieba(DICT_PATH,
        HMM_PATH,
        USER_DICT_PATH,
        IDF_PATH,
        STOP_WORD_PATH);
    vector<string> words;
    string line;
    for(auto& path:_cnPath)
    {
        cout << "path:" << path << endl;
        ifstream ifs(path);
        while(ifs>>line)
        {
            jieba.Cut(line,words,true);
            for(auto& word:words){
                if(is_chinese(word))
                    ++_dict[word];
            }
        }
    }
}

//存储词典文件
void DictProducer::store_dict(const char* filepath)
{

    ofstream ofs(filepath);
    auto it = _dict.begin();
    while(it != _dict.end())
    {
        ofs << it->first << " " << it->second << endl;
        ++it;
    }
}

}//end of namespace std


