#include <stdio.h> 
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
int main()
{
    struct sockaddr_in ser,cli;
    char buf[10]="hello";
    memset(&cli,0,sizeof(cli));
    memset(&ser,0,sizeof(ser));
    ser.sin_family=AF_INET;
    ser.sin_port=htons(9000);
    inet_pton(AF_INET,"127.0.0.1",&ser.sin_addr);

    int i;
    pid_t pid;
    for(i=0;i<200;i++)
    {
        pid = fork();
        if(pid<0)
        {
            perror("fork");
            exit(1);
        }else if(pid==0)
        {
            break;
        }
    }
    if(pid==0)
    {
        int cfd = socket(AF_INET,SOCK_STREAM,0);
        if(-1==connect(cfd,(struct sockaddr*)&ser,sizeof(ser)))
            perror("connect");
        sprintf(buf,"%s%d",buf,i);
        if(-1==write(cfd,buf,sizeof(buf)))
        {
            perror("write");
        }
        if(-1==read(cfd,buf,sizeof(buf)))
        {
            perror("read");
        }
        printf("%s\n",buf);
    }else
    {
        for(i=0;i<200;i++)
            wait(NULL);
    }
    return 0;
}
