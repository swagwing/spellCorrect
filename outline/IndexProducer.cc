#include "IndexProducer.h"

namespace wd
{
size_t nBytesCode(const char ch)
{
    if(ch & (1<<7))
    {
        int nBytes = 1;
        for(int idx = 0;idx != 6;++idx)
        {
            if(ch & (1 << (6-idx)))
            {
                ++nBytes;
            }
            else
                break;
        }
        return nBytes;
    }
    return 1;
}

IndexProducer::IndexProducer(const string& filename)
{
    ifstream ifs(filename);
    string word;
    int frequence;
    while(ifs>>word>>frequence){
        _dict.push_back(make_pair(word,frequence));
    }
}

void IndexProducer::build_index()
{
#if 0
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
#endif
    string word;
    int cnt = 0; //计算下标位置
    for(auto& it : _dict)
    {
        word = it.first;
        string ch;
        int nBytes;
        size_t cur = 0;
        while(cur != word.size())
        {
            nBytes = nBytesCode(word[cur]);
            ch = word.substr(cur,nBytes);
            cur+=nBytes;
            _indexMap[ch].insert(cnt);
        }
        ++cnt;
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
