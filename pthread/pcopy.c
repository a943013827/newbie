#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/types.h>
#include <string.h>
typedef struct
{
    char * f1;
    char * f2;
    int start;
    int size;
    int *p; 
}myfile;
void* pcopy(void* arg)
{
    myfile* mf=(myfile*)arg;
    int fd1=open(mf->f1,O_RDONLY);
    int fd2=open(mf->f2,O_WRONLY);
    lseek(fd1,mf->start,SEEK_SET);
    lseek(fd2,mf->start,SEEK_SET);
    int i;
    char buf[1];
    for(i=0;i<mf->size;i++)
    {
        read(fd1,buf,sizeof(buf));
        write(fd2,buf,sizeof(buf));
        (*(mf->p))++;
        usleep(10);
    }
    close(fd1);
    close(fd2);
}
int main(int argc,char* argv[])
{
    if(argc!=4)
    {
        printf("bad argument");
        exit(1);
    }
    int fd1=open(argv[1],O_RDONLY);
    if(fd1==-1)
    {
        perror(argv[1]);
        exit(1);
    }
    int fd2=open(argv[2],O_WRONLY|O_CREAT|O_TRUNC,0644);
    if(fd2==-1)
    {
        perror(argv[2]);
        exit(1);
    }
    int len=lseek(fd1,0,SEEK_END);
    ftruncate(fd2,len);
    int count=atoi(argv[3]);
    int size=len/count;
    pthread_t *tid=malloc(sizeof(pthread_t)*count);
    myfile* mf=malloc(sizeof(myfile)*count);
    int* p=malloc(sizeof(int)*count);
    memset(p,0,sizeof(p));
    int i;
    for(i=0;i<count;i++)
    {
        mf[i].f1=argv[1];
        mf[i].f2=argv[2];
        mf[i].start=i*size;
        mf[i].p=p+i;
        if(i!=count-1)
        {
            mf[i].size=size;
        }else
        {
            mf[i].size=len%count+size;
        }
        pthread_create(&tid[i],NULL,pcopy,(void*)&mf[i]);
    }
    int n=0;
    while(1)
    {
        int sum=0;
        for(i=0;i<count;i++)
        {
            sum+=p[i];
        }
        for(;n<sum*50/len;n++)
        {
            write(STDOUT_FILENO,"=",1);
        }
        if(sum==len)
        {
            printf("\n");
            break;
        }
    }
    for(i=0;i<count;i++)
    {
        pthread_join(tid[i],NULL);
    }
    close(fd1);
    close(fd2);
    free(tid);
    free(mf);
    free(p);
}
