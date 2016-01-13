#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdio.h>
#include <strings.h>
#include <arpa/inet.h>
#include <string.h>
int main()
{
    struct sockaddr_in ser,cli;
    int i=0;
    int fd=socket(AF_INET,SOCK_STREAM,0);
    memset(&ser,0,sizeof(ser));
    memset(&cli,0,sizeof(cli));
    ser.sin_family=AF_INET;
    //	cli.sin_family=AF_INET;
    ser.sin_port=htons(8000);
    //	cli.sin_port=htons(15000);
    inet_pton(AF_INET,"127.0.0.1",&ser.sin_addr);
    //	inet_pton(AF_INET,"192.168.32.60",&cli.sin_addr);
    //	bind(fd,(struct sockaddr*)&cli,sizeof(cli));

    int ret=connect(fd,(struct sockaddr*)&ser,sizeof(ser));
    if(ret ==-1)
    {
        perror("connect");
        exit(1);
    }
    while(1)
    {
        getchar();
        ret=write(fd,"hello world",11);
        if(ret==-1)
        {
            perror("write");
        }
        printf("%d\n",i++);
    }
    return 0;
}
