#include <unistd.h>
#include <stdio.h>
#include <signal.h>
//当两个信号同时抵达时，内核的行为
void func(int i)
{
    printf("%d\n",i);
}

int main()
{
   sigset_t s1; 
   sigemptyset(&s1);
   sigaddset(&s1,SIGINT);
   sigaddset(&s1,SIGTSTP);
   sigprocmask(SIG_SETMASK,&s1,NULL);
    
   sigemptyset(&s1);
   struct sigaction sa;
   sa.sa_handler=func;
   sa.sa_flags=0;
   sa.sa_mask = s1;
   sigaction(SIGINT,&sa,NULL);
   sigaction(SIGTSTP,&sa,NULL);
   sleep(10);
   sigprocmask(SIG_SETMASK,&s1,NULL);
}
