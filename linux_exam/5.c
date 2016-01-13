#include <unistd.h>
#include <stdio.h>
#include <signal.h>
pid_t  pid;
int i=0;
void catch(int sig)
{
    if(sig==SIGUSR1)
    {
        printf("son:%d\n",i+=2);
        sleep(1);
        kill(getppid(),SIGUSR2);
    }
    if(sig==SIGUSR2)
    {
        printf("father:%d\n",i+=2);
        sleep(1);
        kill(pid,SIGUSR1);
    }
}
int main()
{
    struct sigaction s;
    s.sa_handler=catch;
    s.sa_flags=0;
    sigemptyset(&s.sa_mask);
    if(sigaction(SIGUSR1,&s,NULL)==-1)
    {
        perror("sigaction");
    }
    if(sigaction(SIGUSR2,&s,NULL)==-1)
    {
        perror("sigaction");
    }
    pid=fork();
    if(pid==-1)
    {
        perror("fork");
    }
    if(pid==0)
    {
        while(1);
    }else
    {
        i=1; 
        kill(pid,SIGUSR1);
        while(1);
    }
}
