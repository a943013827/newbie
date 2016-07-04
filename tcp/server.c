#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <strings.h>
#include <arpa/inet.h>
#include <string.h>
int main()
{

    struct sockaddr_in ser;
    int fd=socket(AF_INET,SOCK_STREAM,0);
    memset(&ser,0,sizeof(ser));
    ser.sin_family = AF_INET;
    ser.sin_port=htons(8000);
    inet_pton(AF_INET,"127.0.0.1",&ser.sin_addr);
    bind(fd,(struct sockaddr*)&ser,sizeof(ser));
    perror("");
    char buf0[20]={0};
    read(0,buf0,20);
    listen(fd,1);
    perror("");
    read(STDIN_FILENO,buf0,20);
    char buf[20]={0};
    struct sockaddr_in cli;
    socklen_t len= sizeof(cli);
    printf("server ready\n");
    while(1)
    {
        int fd2=accept(fd,(struct sockaddr*)&cli,&len);
        perror("");
        printf("client ip:%s,client port:%d\n",inet_ntop(AF_INET,&cli.sin_addr,buf,sizeof(buf)),ntohs(cli.sin_port));
        read(fd2,buf,sizeof(buf));
        printf("%s\n",buf);
        close(fd2);
    }
    close(fd);
    return 0;
}
