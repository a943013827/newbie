#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
int main()
{
    int pid =fork();
    char buf[1024]={0};
    if(pid==0)
    {
        int i=read(STDIN_FILENO,buf,1024);
        strcat(buf," son");
        write(STDOUT_FILENO,buf,strlen(buf));
    }else
    {
        sleep(1);
        int i=read(STDIN_FILENO,buf,1024);
        strcat(buf," father");
        write(STDOUT_FILENO,buf,strlen(buf));
    }
}
