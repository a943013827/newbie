#include <pthread.h>
#include <unistd.h>
#include <stdio.h>


void* func(void* p)
{
    while(1);
}
int main()
{
    pthread_t tid;
    int i=0;
    while(1)
    {
        if(0!=pthread_create(&tid,NULL,func,NULL))
            break;
        i++;
        printf("%d\n",i);
    }
    return 0;
}
