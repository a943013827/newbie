#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/mman.h>
void* func(void* p)
{
}

int main()
{
    int fd =open("a.txt",O_RDWR,0644);
    perror(" ");
    void * p=mmap(NULL,1024,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    perror(" ");
    printf("%p\n",p);
    int i;
    while(1)
    {
        i=*(int*)p;
        printf("%d\n",i);
        sleep(1);
    }
    return 0;
}
