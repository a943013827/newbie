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

int main(void)
{
    int cfd = socket(AF_UNIX,SOCK_STREAM,0);
    perror("socket");
    struct sockaddr_un ser,cli;
    memset(&ser,0,sizeof(ser));
    memset(&cli,0,sizeof(cli));
    char buf[1024]={0};
    cli.sun_family = AF_UNIX;
    strcpy(cli.sun_path,"/home/mage/cli.sock");
    int len=offsetof(struct sockaddr_un,sun_path)+strlen("/home/mage/cli.sock");
    unlink("/home/mage/cli.sock");
    if(-1== bind(cfd,(struct sockaddr*)&cli,len))
        perror("bind");
    ser.sun_family=AF_UNIX;
    strcpy(ser.sun_path,"/home/mage/ser.sock");
    len =offsetof(struct sockaddr_un,sun_path)+strlen("/home/mage/ser.sock");
    if(-1==connect(cfd,(struct sockaddr*)&ser,len))
        perror("connect");
    while(fgets(buf,sizeof(buf),stdin)!=NULL)
    {
        write(cfd,buf,strlen(buf));
        len = read(cfd,buf,sizeof(buf));
        buf[len]=0;
        write(STDOUT_FILENO,buf,len);
    }
    unlink("/home/mage/cli.sock");
    close(cfd);
}
