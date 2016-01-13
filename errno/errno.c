#include <errno.h>
#include <stdio.h>
//#include <pthread.h>
void * func(void * p)
{
    printf("%u\n",&errno);
}
int x;
int main()
{
    int a;
    printf("errno:%u  x:%u a:%u\n",&errno,&x,&a);
//    pthread_t tid;
//    pthread_create(&tid,NULL,func,NULL);
//    pthread_join(tid,NULL);
}

