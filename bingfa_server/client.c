#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

int main()
{
    struct sockaddr_in ser,cli;
    char buf[1024];
    int count;
    memset(&ser,0,sizeof(ser));
    ser.sin_family=AF_INET;
    ser.sin_port=htons(8000);
    inet_pton(AF_INET,"127.0.0.1",&ser.sin_addr.s_addr);
    int cfd=socket(AF_INET,SOCK_STREAM,0);
    connect(cfd,(struct sockaddr*)&ser,sizeof(ser));
    while((count=read(STDIN_FILENO,buf,sizeof(buf)))!=0)
    {
        write(cfd,buf,count);
    }
    close(cfd);
}
