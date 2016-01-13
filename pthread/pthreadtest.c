#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <stdlib.h>
void* func(void* p)
{
    int a;
    printf("sonstack:%u  son_thread:%u\n",(unsigned int)&a,(unsigned int)pthread_self());
}

int main(int argc, char* argv[])
{
    int a;
    printf("argv:%u  main_stack:%u\n",(unsigned int)argv,(unsigned int)&a);
    printf("malloc:%u\n",(unsigned int)malloc(1024));
    pthread_t tid;    
    pthread_create(&tid,NULL,func,NULL);
    printf("main_thread:%u  son_thread:%u\n",(unsigned int)pthread_self(),(unsigned int)tid);
    int fd =open("a.txt",O_RDWR|O_CREAT|O_TRUNC,0644);
    ftruncate(fd,1024);
    perror(" ");
    void * p=mmap(NULL,1024,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    perror(" ");
    printf("mamp:%u\n",(unsigned int)p);
    pthread_join(tid,NULL);
    int i=0;
    while(1)
    {
        *(int*)p=i;
        i++;
        sleep(1);
    }
    return 0;
}
