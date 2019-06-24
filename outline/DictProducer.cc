#include "DictProducer.h"

namespace wd
{

bool cmp(const pair<string,int> &lhs,const pair<string,int> &rhs)
{
    return lhs.second > rhs.second;
}

void mytolower(string& s)
{
    int len = s.length();
    for(int i=0; i<len; ++i){
        if(s[i] >= 'A' && s[i] <= 'Z'){
            s[i] += 32;
        }
    }
}

DictProducer::DictProducer(const string& filename)
    :_dir(filename)
{}

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

//存储词典文件
void DictProducer::store_dict(const char* filepath)
{

    ofstream ofs(filepath);
    vector<pair<string,int>> dict_map(_dict.begin(),_dict.end());
    sort(dict_map.begin(),dict_map.end(),cmp);
    auto it = dict_map.begin();
    while(it != dict_map.end())
    {
        ofs << it->first << " " << it->second << endl;
        ++it;
    }
}

}//end of namespace std


