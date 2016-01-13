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
    int len;
    int sfd = socket(AF_UNIX,SOCK_STREAM,0);
    if(sfd==-1)
        perror("socket");
    struct sockaddr_un ser,cli;
    char buf[1024]={0};

    memset(&ser,0,sizeof(ser));
    ser.sun_family=AF_UNIX;
    strcpy(ser.sun_path,"/home/mage/ser.sock");

    len=offsetof(struct sockaddr_un,sun_path)+strlen("/home/mage/ser.sock");
    unlink("/home/mage/ser.sock");
    if(-1== bind(sfd,(struct sockaddr*)&ser,len))
        perror("bind");
    if(-1==listen(sfd,20))
        perror("listen");

    int fd;
    int i;
    int count;
    len=sizeof(cli);
    pid_t pid = fork();
    if(pid==0)
    {
        if(-1==(fd=accept(sfd,(struct sockaddr*)&cli,&len)))
            perror("accept");
        len-=offsetof(struct sockaddr_un,sun_path);
        cli.sun_path[len]=0;
        printf("%s\n",cli.sun_path);
        while(1)
        {
            count=read(fd,buf,2);
            for(i=0;i<count;i++)
                buf[i]=toupper(buf[i]);
            write(fd,buf,count);
        }
        close(fd);
        close(sfd);
    }else
    {
        sleep(1);
        if(-1==(fd=accept(sfd,(struct sockaddr*)&cli,&len)))
            perror("accept");
        len-=offsetof(struct sockaddr_un,sun_path);
        cli.sun_path[len]=0;
        printf("%s\n",cli.sun_path);
        while(1)
        {
            count=read(fd,buf,2);
            for(i=0;i<count;i++)
                buf[i]=toupper(buf[i]);
            write(fd,buf,count);
        }
        close(fd);
        close(sfd);
    }
}
