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
    char buf[1024]="hello world";
    char buf2[1024]={0};
    memset(&cli,0,sizeof(cli));
    cli.sun_family=AF_UNIX;
    strcpy(cli.sun_path,"udpc.sock");
    int len = offsetof(struct sockaddr_un,sun_path)+strlen("udpc.sock");
    int cfd=socket(AF_UNIX,SOCK_DGRAM,0);
    unlink("udpc.sock");
    if(-1==bind(cfd,(struct sockaddr*)&cli,len))
        perror("bind");
    memset(&ser,0,sizeof(cli));
    ser.sun_family=AF_UNIX;
    strcpy(ser.sun_path,"udps.sock");
    len=offsetof(struct sockaddr_un,sun_path)+strlen("udps.sock");
    while(1)
    {
    int count = read(STDIN_FILENO,buf,sizeof(buf));
    sendto(cfd,buf,strlen(buf),0,(struct sockaddr*)&ser,len);
    recvfrom(cfd,buf2,sizeof(buf2),0,(struct sockaddr*)&ser,&len);
    printf("%s\n",buf2);
    }
    unlink("udpc.sock");
}
