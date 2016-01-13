#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/epoll.h>
#include <errno.h>

int main()
{
    struct sockaddr_in ser,cli;
    int len = sizeof(cli);
    char buf[1024];
    char ipbuf[20];

    int sfd = socket(AF_INET,SOCK_STREAM,0);
    memset(&ser,0,sizeof(ser));
    ser.sin_family=AF_INET;
    ser.sin_port=htons(9000);
    inet_pton(AF_INET,"127.0.0.1",&ser.sin_addr);

    bind(sfd,(struct sockaddr*)&ser,sizeof(ser));

    listen(sfd,100);

    int	efd = epoll_create(1024);
    if(efd==-1)
    {
        perror("epoll");
        exit(1);
    }
    struct epoll_event ep, eplist[1024];
    ep.events = EPOLLIN;
    ep.data.fd=sfd;
    if(-1==epoll_ctl(efd,EPOLL_CTL_ADD,sfd,&ep))
    {
        perror("epoll_ctl");
        exit(1);
    }
    while(1)
    {
        int ready = epoll_wait(efd,eplist,1024,-1);
        if(ready==-1)
        {
            perror("epoll_wait");
            exit(1);
        }
        int i;
        for(i=0;i<ready;i++)
        {
            if(eplist[i].events&EPOLLIN)
            {
                if(eplist[i].data.fd==sfd)
                {
                    int fd = accept(sfd,(struct sockaddr*)&cli,&len);
                    ep.events=EPOLLIN;
                    ep.data.fd=fd;
                    if(-1== epoll_ctl(efd,EPOLL_CTL_ADD,fd,&ep))
                    {
                        perror("epoll_ctl");
                        exit(1);
                    }
                    printf("%s,%d\n",inet_ntop(AF_INET,&cli.sin_addr,ipbuf,sizeof(ipbuf)),ntohs(cli.sin_port));

                }else
                {
                    int count = read(eplist[i].data.fd,buf,sizeof(buf));
                    if(count=0)
                    {
                        close(eplist[i].data.fd);
                        epoll_ctl(efd,EPOLL_CTL_DEL,eplist[i].data.fd,NULL);
                    }else if(count < 0)
                    {
                        perror("read");
                        exit(1);
                    }else
                    {
                        int n;
                        for(n=0;n<count;n++)
                        {
                            buf[n]=toupper(buf[n]);
                        }
                        write(eplist[i].data.fd,buf,count);
                    }
                }
            }
        }
    }
}
