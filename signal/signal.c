#include <stdio.h>
#include <signal.h>

int main()
{
    sigset_t s1,s2;
    sigfillset(&s1);
    sigprocmask(SIG_SETMASK,&s1,NULL);
    while(1)
    {
        sigpending(&s2);
        int i;
        for(i=1;i<32;i++)
        {
            if(sigismember(&s2,i)==1)
            {
                printf("%d",1);
            }else
            {
                printf("%d",0);
            }
        }
        putchar(10);
        sleep(1);
    }
}
