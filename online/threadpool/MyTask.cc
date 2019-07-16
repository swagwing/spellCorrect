#include "MyTask.h"
#include "MyDict.h"
#include "Thread.h"

namespace wd
{

size_t nBytesCode(const char ch)
{
    if(ch & (1 << 7))
    {
        int nBytes = 1;
        for(int idx = 0;idx != 6; ++idx)
        {
            if(ch & (1 << (6-idx))){
                ++nBytes;
            }
            else
                break;
        }
        return nBytes;
    }
    return 1;
}

size_t length(const string& str)
{
    size_t ilen = 0;
    for(size_t idx=0; idx!=str.size(); ++idx)
    {
        int nBytes = nBytesCode(str[idx]);
        idx += (nBytes - 1);
        ++ilen;
    }
    return ilen;
}

string wordFilter(string word)
{
    char word_tmp[50];
    word_tmp[0] = word[0];
    int j=0,flag;
    for(int i = 0;i<word.length();++i)
    {
        flag = 1;
        for(int k=0;k<j+1;++k){
            if(word[i]==word_tmp[k])
                flag = 0;
        }
        if(flag){
            j = j+1;
            word_tmp[j] = word[i];
        }
    }
    word_tmp[j+1] = '\0';
    word = word_tmp;
    return word;
}

MyTask::MyTask(const string& queryWord,const TcpConnectionPtr& conn,MyDict* pInstance,CacheManager* pCacheM)
    :_conn(conn)
    ,_queryWord(queryWord)
    ,_pInstance(pInstance)
     ,_pCacheM(pCacheM)
{}

void MyTask::execute()
{
    cout << "enter MyTask::execute" << endl;
    cout << "MyTask::execute-->threadNum: " << threadNum << endl; //***threadNum获取正确
    Cache& iCache = _pCacheM->getCache(threadNum); //***第一次问题所在
    string response;
    if(iCache.search(_queryWord) != string()){
        response = iCache.search(_queryWord);
        cout << "in cache(iHotData)->reaponse: " << response << endl; //***测试信息
    }else{
        if(_pCacheM->searchMainCache((_queryWord)) != string()){
            response = _pCacheM ->searchMainCache(_queryWord);
            cout << "in cache(cacheM)->response: " << response << endl; //***测试信息
        }else{
            queryIndexTable();
            MyResult result;
            Json::Value root;
            for(int cnt=1; cnt <= 3; ++cnt){
                result = _resultQue.top();
                root["word_candidate"].append(result._word);
                _resultQue.pop();
            }
            Json::FastWriter fast_writer;
            response = fast_writer.write(root);
            cout << "not in Cache-> response: " << response << endl;
            iCache.addElement(_queryWord,response);
            list<pair<string,string>> ilist;
            ilist = iCache.getHotData();
            //ilist.push_back(make_pair(_queryWord,response));
            cout << "MyTask::execute else else-->ilist" << endl; //***测试信息
            auto it = ilist.begin();
            while(it != ilist.end()){
                cout << it->first << " " << it->second << endl;
                ++it;
            }
        }
    }
    _conn->sendInLoop(response);
}

void MyTask::queryIndexTable()
{
    string tmp;
    if(isalpha(_queryWord[0]))
        tmp = wordFilter(_queryWord);
    else
        tmp = _queryWord;
    map<string,set<int>> index;
    set<int> iset;
    set<int> tset;
    index = _pInstance->getIndexTable();
    size_t cur = 0;
    int nBytes;
    string ch;
    while(cur != tmp.size())
    {
        nBytes = nBytesCode(tmp[cur]);
        ch = tmp.substr(cur,nBytes);
        iset = index[ch];
        tset.insert(iset.begin(),iset.end());
        cur += nBytes;
    }
    statistic(tset);
    //response();
}

void MyTask::statistic(set<int>& iset)
{
    string candidateWord;
    int CurDistance;
    vector<pair<string,int>> dict;
    MyResult result;
    dict = _pInstance->getDict();
    auto it = iset.begin();
    while(it != iset.end()){
        candidateWord = dict[*it].first;
        CurDistance = distance(candidateWord);
        result._word = candidateWord;
        result._iFreq = dict[*it].second;
        result._iDict = CurDistance;
        _resultQue.push(result);
        ++it;
    }
}

int MyTask::distance(const string& rhs)
{
    int dp[1005][1005];
    dp[0][0] = 0;
    int len1 = length(_queryWord);
    int len2 = length(rhs);
    for(int i = 1; i <= len1; ++i)
        for(int j = 1;j <= len2; ++j)
            dp[i][j] = INF;
    for(int i = 1; i <= len1; ++i)
        dp[i][0] = i;
    for(int j = 1; j <= len2; ++j)
        dp[0][j] = j;
    for(int i = 1; i <= len1; ++i)
    {
        for(int j = 1; j <= len2; ++j)
        {
            int flag;
            if(_queryWord[i-1] == rhs[j-1])
                flag = 0;
            else
                flag =1;
            dp[i][j] = min(dp[i-1][j]+1,min(dp[i][j-1]+1,dp[i-1][j-1]+flag));
        }
    }
    return dp[len1][len2];
}

void MyTask::response()
{
    MyResult result;
    Json::Value root;
    for(int cnt=1; cnt <= 3; ++cnt){
        result = _resultQue.top();
        root["word_candidate"].append(result._word);
        _resultQue.pop();
    }
    Json::FastWriter fast_writer;
    string response = fast_writer.write(root);
    cout << "not in Cache-> response: " << response << endl;
    //_conn->sendInLoop(response); //暂时注释掉
}

}//end of namespace wd
