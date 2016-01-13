#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
int main()
{
    int i;
    int ret;
    for(i=0;i<1;i++)
    {
        if((ret=fork())==-1)
        {
            perror("fork");
        }
        else if(ret==0)
        {
            break;
        }
    }
    if(i==0)
    {
        int n=getppid();
        printf("%d\n",n);
        sleep(10);
        if(kill(n,SIGKILL)==-1)
            perror("kill");
    }else if(i==1)
    {
        wait(NULL);
    }
    return 0;

}
