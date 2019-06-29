 ///
 /// @file    TcpConnection.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-05-07 17:12:51
 ///
 

#include "TcpConnection.h"
#include "InetAddress.h"
#include "EventLoop.h"
#include <errno.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <iostream>
#include <sstream>
#include <string.h>
using namespace std;

namespace wd
{
TcpConnection::TcpConnection(int fd, EventLoop * loop)
: _sock(fd)
, _socketIo(fd)
, _localAddr(getLocalAddr(fd))
, _peerAddr(getPeerAddr(fd))
, _isShutdwonWrite(false)
, _loop(loop)
{
}

TcpConnection::~TcpConnection()
{
	if(!_isShutdwonWrite) {
		shutdown();
	}
}

string TcpConnection::receive()
{
	char buff[1000] = {0};
    int data_len;
    _socketIo.recv_cyle((char*)&data_len,4);
    _socketIo.recv_cyle(buff,data_len);
	return string(buff);
}
	
void TcpConnection::send(const string & msg)
{
    train t;
    strcpy(t.buf,msg.c_str());
    t.dataLen = msg.size();
	_socketIo.send_cycle((char*)&t,4+t.dataLen);
}

void TcpConnection::sendInLoop(const string & msg)
{
	_loop->runInLoop(std::bind(&TcpConnection::send, this, msg));
}

void TcpConnection::shutdown()
{
	if(!_isShutdwonWrite) {
		_isShutdwonWrite = true;
		_sock.shutdownWrite();
	}
}

string TcpConnection::toString() const
{
	std::ostringstream oss;
	oss << _localAddr.ip() << ":" << _localAddr.port() << " --> "
		<< _peerAddr.ip() << ":" << _peerAddr.port();
	return oss.str();
}


InetAddress TcpConnection::getLocalAddr(int fd)
{
	struct sockaddr_in addr;
	socklen_t len = sizeof(struct sockaddr);
	if(getsockname(_sock.fd(), (struct sockaddr*)&addr, &len) == -1) {
		perror("getsockname");
	}
	return InetAddress(addr);
}

InetAddress TcpConnection::getPeerAddr(int fd)
{
	struct sockaddr_in addr;
	socklen_t len = sizeof(struct sockaddr);
	if(getpeername(_sock.fd(), (struct sockaddr*)&addr, &len) == -1) {
		perror("getpeername");
	}
	return InetAddress(addr);
}

void TcpConnection::setConnectionCallback(const TcpConnectionCallback & cb)
{
	_onConnection = std::move(cb);
}

void TcpConnection::setMessageCallback(const TcpConnectionCallback & cb)
{
	_onMessage = std::move(cb);
}

void TcpConnection::setCloseCallback(const TcpConnectionCallback & cb)
{
	_onClose = std::move(cb);
}

void TcpConnection::handleConnectionCallback()
{
	if(_onConnection) {
		_onConnection(shared_from_this());
	}
}

void TcpConnection::handleMessageCallback()
{
	if(_onMessage) {
		_onMessage(shared_from_this());
	}
}

void TcpConnection::handleCloseCallback()
{
	if(_onClose) {
		_onClose(shared_from_this());
	}
}

}//end of namespace wd
