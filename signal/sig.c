#include <signal.h>
#include <unistd.h>
#include <stdio.h>

int n=0;

void func(int i)
{
    n++;
}


int main()
{
    sigset_t mask;
    sigemptyset(&mask);
    struct sigaction sa;
    sa.sa_handler=func;
    sa.sa_flags=0;
    sa.sa_mask=mask;
    sigaction(SIGINT,&sa,NULL);
    pid_t pid = fork();
    if(pid==0)
    {
        sleep(3);
        printf("%d\n",n);
    }else
    {
        int i;
        for(i=0;i<10;i++)
            kill(pid,SIGINT);
    }

}
