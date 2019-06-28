 ///
 /// @file    SocketIO.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-05-07 16:01:31
 ///
 

#include "SocketIO.h"
#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>

using namespace std;
namespace wd
{

SocketIO::SocketIO(int fd)
: _fd(fd)
{}

int SocketIO::readn(char * buff, int len)
{
	int left = len;
	char * p = buff;
	while(left > 0) {
		int ret = ::read(_fd, p, left);
		if(ret == -1 && errno == EINTR)
			continue;
		else if(ret == -1) {
			perror("read");
			return len - left;
		}
		else if(ret == 0) {
			return len - left;
		} else {
			left -= ret;
			p += ret;
		}
	}
	return len - left;
}

//每一次读取一行数据
int SocketIO::readline(char * buff, int maxlen)
{
	int left = maxlen - 1;
	char * p = buff; 
	int ret;
	int total = 0;
	while(left > 0) {
		ret = recvPeek(p, left);		
		//查找 '\n'
		for(int idx = 0; idx != ret; ++idx) {
			if(p[idx] == '\n') {
				int sz = idx + 1;
				readn(p, sz);
				total += sz;
				p += sz;
				*p = '\0';
				return total;
			}
		}
		//如果没有发现 '\n'
		readn(p, ret);
		left -= ret;
		p += ret;
		total += ret;
	}
	*p = '\0';// 最终没有发现'\n'
	return total;
}

int SocketIO::recvPeek(char * buff, int len)
{
	int ret;
	do {
		ret = ::recv(_fd, buff, len, MSG_PEEK);
	} while(ret == -1 && errno == EINTR);
	return ret;
}

	
int SocketIO::writen(const char * buff, int len)
{
	int left = len;
	const char * p = buff;
	while(left > 0) {
		int ret = ::write(_fd, p, left);
		if(ret == -1 && errno == EINTR)
			continue;
		else if(ret == -1) {
			perror("write");
			return len - left;
		} else {
			left -= ret;
			p += ret;
		}
	}
	return len - left;
}

int SocketIO::send_cycle(const char* buf,int len)
{
    int total = 0;
    int ret;
    while(total < len)
    {
        ret = send(_fd,buf+total,len-total,0);
        if(-1 == ret)
        {
            cout << "errno = " << errno << endl;
            return -1;
        }
        total = total + ret;
    }
    return 0;
}

int SocketIO::recv_cyle(char* buf,int len)
{
    int total = 0;
    int ret;
    while(total< len)
    {
        ret = recv(_fd,buf+total,len-total,0);
        total = total + ret;
    }
    return 0;
}

}//end of namespace wd
