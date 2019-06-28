 ///
 /// @file    SocketIO.h
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-05-07 15:59:16
 ///
 
#ifndef __WD_SOCKETIO_H__
#define __WD_SOCKETIO_H__

namespace wd
{

struct train
{
    int dataLen;
    char buf[1000];
};

class SocketIO
{
public:
	explicit
	SocketIO(int fd);

	int readn(char * buff, int len);
	int readline(char * buff, int maxlen);
	int writen(const char * buff, int len);
    int send_cycle(const char*,int);
    int recv_cyle(char*,int);
private:
	int recvPeek(char * buff, int len);

private:
	int _fd;
};

}//end of namespace wd

#endif 
