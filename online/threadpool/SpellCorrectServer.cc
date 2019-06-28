#include "SpellCorrectServer.h"
namespace wd
{

SpellCorrectServer::SpellCorrectServer(const string& cfgFileName)
    :_conf(cfgFileName)
    ,_tcpserver(_conf.getConfigMap().find("ip")->second,stoi(_conf.getConfigMap().find("port")->second))
    ,_threadpool(4,10)
{}

void SpellCorrectServer::onConnection(const TcpConnectionPtr& conn)
{
    cout << conn->toString() << "has Connected!" << endl;
    conn->send("welcome to server.");
}

void SpellCorrectServer::onMessage(const TcpConnectionPtr& conn)
{
    cout << "onMessage...." << endl;
    string msg = conn ->receive();
    cout << ">> receive msg from client: " << msg << endl;
    MyDict* pInstance = MyDict::createInstance();
    pInstance->init(_conf.getConfigMap().find("dictPath")->second,_conf.getConfigMap().find("indexPath")->second);
    MyTask task(msg,conn,pInstance);
    _threadpool.addTask(std::bind(&MyTask::queryIndexTable,task));
}

void SpellCorrectServer::onClose(const TcpConnectionPtr& conn)
{
    cout << "onClose....." << endl;
    cout << conn->toString() << "has closed!" << endl;
}

using namespace std::placeholders;
void SpellCorrectServer::start()
{//using namespace std::placeholders;
    _threadpool.start();
    _tcpserver.setConnectionCallback(bind(&SpellCorrectServer::onConnection,this,_1));  
    _tcpserver.setMessageCallback(bind(&SpellCorrectServer::onMessage,this,_1));
    _tcpserver.setCloseCallback(bind(&SpellCorrectServer::onClose,this,_1));
    _tcpserver.start();
}
}//end of namespace wd
