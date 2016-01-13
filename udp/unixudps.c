#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>         
#include <sys/socket.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <sys/un.h>
#include <stddef.h>

int main()
{
    struct sockaddr_un ser,cli;
    char buf[1024]={0};
    memset(&ser,0,sizeof(ser));
    ser.sun_family=AF_UNIX;
    strcpy(ser.sun_path,"udps.sock");
    int sfd=socket(AF_UNIX,SOCK_DGRAM,0);
    int len = offsetof(struct sockaddr_un,sun_path)+strlen("udps.sock");
    if(-1==bind(sfd,(struct sockaddr*)&ser,len))
        perror("bind");
    while(1)
    {
    int count = recvfrom(sfd,buf,2,0,(struct sockaddr*)&cli,&len);
    int i;
    for(i=0;i<count;i++)
        buf[i]=toupper(buf[i]);
    sendto(sfd,buf,count,0,(struct sockaddr*)&cli,len);
    }
    unlink("udps.sock");
}
