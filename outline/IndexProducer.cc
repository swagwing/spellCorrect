#include "IndexProducer.h"

namespace wd
{
IndexProducer::IndexProducer(vector<pair<string,int>>& dict)
    :_dict(dict)
{}

void IndexProducer::build_index()
{
    char ch = 'a';
    while(ch <= 'z'){
        set<int> alpha;
        auto it = _dict.begin();
        int cnt = 0; //计算单词的下标位置
        while(it != _dict.end()){
            string word = it->first;
            int len = word.length();
            int i = 0;
            while(i <= len){
                if(word[i] == ch){
                    alpha.insert(cnt);
                    break;
                }
                ++i;
            }
            ++it;
            ++cnt;
        }
        string str(1,ch);
        _indexMap.insert({str,alpha});
        ++ch;
    }
}

void IndexProducer::store_index(const char* filepath)
{
    ofstream ofs(filepath);
    auto it = _indexMap.begin();
    while(it != _indexMap.end()){
        ofs << it->first << endl;
        auto iset = it->second.begin();
        while(iset != it->second.end()){
            ofs << *iset << " ";
            ++iset;
        }
        ofs << endl;
        ++it;
    }
}

}//end of namespace wd
