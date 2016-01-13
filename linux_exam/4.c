#include<unistd.h>
#include <stdio.h>
#include <string.h>
int main()
{
    int fd[2];
    if(pipe(fd)==-1)
        perror("pipe");
    pid_t pid=fork();
    if(pid==-1)
        perror("fork");
    if(pid==0)
    {
        close(fd[0]);
        dup2(fd[1],STDOUT_FILENO);
        execlp("ps","ps","aux",NULL);
    }else
    {
        close(fd[1]);
        dup2(fd[0],STDIN_FILENO);
        char buf[1024];
        char *s;
        int id;
        int count=0;
        while(NULL!= gets(buf))
        {
            strtok(buf," ");
            s=strtok(NULL," ");
            id=atoi(s);
            if(id>4000&&id<5000)
            {
                count++;
            }
        }
        printf("%d\n",count);
    }

}
