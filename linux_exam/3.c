#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc,char* args[])
{
    if(argc!=3&&argc!=4)
    {
        printf("bad argument");
        exit(1);
    }
    if(argc==4)
    {
        int fd0 = open(args[3],O_WRONLY|O_CREAT|O_TRUNC,0644);
        dup2(fd0,STDOUT_FILENO);
    }
    int fd1=open(args[1],O_RDONLY);
    if(fd1==-1)
    {
        perror(args[1]);
    }
    int fd2=open(args[2],O_RDONLY);
    if(fd2==-1)
    {
        perror(args[2]);
    }
    char buf[1024];
    int ret;
    while((ret=read(fd1,buf,1024))!=0)
    {
        write(STDOUT_FILENO,buf,ret);
    }
    while(1)
    {
        ret=read(STDIN_FILENO,buf,1024);
        if(ret==0)
        {
            break;
        }
        write(STDOUT_FILENO,buf,ret);
    }
    while((ret=read(fd2,buf,1024))!=0)
    {
        write(STDOUT_FILENO,buf,ret);
    }
    return 0;

}
