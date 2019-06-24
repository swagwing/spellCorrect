#include "MyTask.h"
#include "MyDict.h"

namespace wd
{

MyTask::MyTask(const string& queryWord)
    :_queryWord(queryWord)
{}

void MyTask::statistic(set<int>& iset)
{
    string candidateWord;
    int CurDistance;
    vector<pair<string,int>> dict;
    MyResult result;
    wd::MyDict* pInstance = wd::MyDict::createInstance();
    dict = pInstance->getDict();
    auto it = iset.begin();
    while(it != iset.end()){
        candidateWord = dict[*it].first;
        CurDistance = distance(candidateWord);
        result._word = candidateWord;
        result._iFreq = dict[*it].second;
        result._iDict = CurDistance;
        _resultQue.push(result);
    }
}

int MyTask::distance(const string& rhs)
{
    int dp[1005][1005];
    dp[0][0] = 0;
    int len1 = _queryWord.length();
    int len2 = rhs.length();
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

}//end of namespace wd
