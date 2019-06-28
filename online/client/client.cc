#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <json/json.h>
#define ERR_EXIT(m) \
    do { \
        perror(m);\
        exit(EXIT_FAILURE);\
    }while(0)
#define ERROR_CHECK(ret,retval,funcName) {if(ret == retval)\
    {perror(funcName); return -1;}}
struct train
{
    int dataLen;
    char buf[1000];
};

using namespace std;

int send_n(int sfd,char* buf,int len)
{
    int total = 0;
    int ret;
    while(total < len)
    {
        ret = send(sfd,buf+total,len-total,0);
        if(-1 == ret){
            cout << "errno = " << errno << endl;
            return -1;
        }
        total = total + ret;
    }
    return 0;
}

int recv_n(int sfd,char* buf,int len)
{
    int total = 0;
    int ret;
    while(total < len)
    {
        ret = recv(sfd,buf+total,len-total,0);
        total = total + ret;
    }
    return 0;
}

int do_service(int sockfd);

int main(int argc, const char *argv[])
{
    int peerfd = socket(PF_INET, SOCK_STREAM, 0);
    if(peerfd == -1)
        ERR_EXIT("socket");

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof addr);
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("192.168.233.129"); //localhost
    addr.sin_port = htons(2000);
    socklen_t len = sizeof addr;
    if(connect(peerfd, (struct sockaddr*)&addr, len) == -1)
        ERR_EXIT("Connect");

    char buf[1000];
    memset(buf, 0, sizeof(buf));
    read(peerfd, buf, sizeof(buf));
    printf("%s\n", buf);

    do_service(peerfd);
    return 0;
}


int do_service(int sockfd)
{
    train t;
    char recvbuf[1000] = {0};
    char sendbuf[1000] = {0};
    while(1)
    {
        int ret;
        int data_len;
        cin >> sendbuf;
        t.dataLen = strlen(sendbuf);
        strcpy(t.buf,sendbuf);
        cout << "t.dataLen: " << t.dataLen << endl;
        cout << "t.buff: " << t.buf << endl;
        ret = send_n(sockfd,(char*)&t,4+t.dataLen);
        ERROR_CHECK(ret,-1,"send_n");
        //sleep(5);
        //read
        ret = recv_n(sockfd,(char*)&data_len,4);
        if(-1 == ret){
            cout << "server is not online" << endl;
            break;
        }
        ret = recv_n(sockfd,recvbuf,data_len);
        cout << "receive: " << recvbuf << endl;
        memset(recvbuf, 0, sizeof recvbuf);
        memset(sendbuf, 0, sizeof sendbuf);
    }
}




