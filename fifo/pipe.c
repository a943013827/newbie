#include <unistd.h>
#include <stdio.h>
int main()
{
    int pipefd[2];
    pipe(pipefd);
    int pid=fork();
    char buf[10];
    if(pid==0)
    {
        while(1)
        {
            write(pipefd[1],"hello",6);
            sleep(1);
            read(pipefd[0],buf,10);
            sleep(1);
            printf("%s\n",buf);
        }
    }else
    {
        while(1)
        {
            read(pipefd[0],buf,10);
            sleep(1);
            write(pipefd[1],"father",7);
            sleep(1);
            printf("%s\n",buf);
        }
    }
}
