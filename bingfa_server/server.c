#include <sys/socket.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <sys/types.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>


void func(int i)
{
    waitpid(-1,NULL,0);
    printf("get it \n");
}
int main()
{
    struct sockaddr_in ser,cli;
    char buf[1024];
    int count ;
    int len =sizeof(cli);
    pid_t pid;
    struct sigaction s;
    s.sa_handler=func;
    s.sa_flags=0;
    sigemptyset(&s.sa_mask);
    sigaction(SIGCHLD,&s,NULL);

    memset(&ser,0,sizeof(ser));
    ser.sin_family=AF_INET;
    ser.sin_port=htons(8000);
    inet_pton(AF_INET,"127.0.0.1",&ser.sin_addr.s_addr);

    int sfd=socket(AF_INET,SOCK_STREAM,0);
    bind(sfd,(struct sockaddr*)&ser,sizeof(ser));
    listen(sfd,10);
    while(1)
    {
        int fd;
tab:    if((fd = accept(sfd,(struct sockaddr*)&ser,&len))<0)
            if(errno==ECONNABORTED||errno==EINTR)
                goto tab;
            else
                exit(1);
        pid = fork();
        if(pid==-1)
        {
            perror("fork");
            exit(1);
        }else if(pid==0)
        {
            close(sfd);
            while((count = read(fd,buf,sizeof(buf)))>0)
            {
                buf[count]=0;
                printf("%s",buf);
            }
            close(fd);
            exit(1);
        }else
        {
            close(fd);
        }
    }
    close(sfd);
}
