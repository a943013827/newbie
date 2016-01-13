#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>
#include <stdlib.h>
int buf[10];
pthread_mutex_t m;
sem_t pro,cust;

int count;
int index1,index2;
void* pro1(void* p)
{
    while(1)
    {
        sleep(rand()%5);
        sem_wait(&pro);
        pthread_mutex_lock(&m);
        buf[index1]=count;
        index1=(index1+1)%10;
        printf("pro:%d put %d\n",(int)p,count);
        count++;
        pthread_mutex_unlock(&m);        
        sem_post(&cust);
    }
    return NULL;
}

void *cust1(void* p)
{
    while(1)
    {
        sleep(rand()%5);
        sem_wait(&cust);
        pthread_mutex_lock(&m);
        printf("cust:%d  fetch %d\n",(int)p,buf[index2]);
        index2=(index2+1)%10;
        pthread_mutex_unlock(&m);
        sem_post(&pro);
    }
    return NULL;
}

int main()
{
    pthread_t tid[10];
    sem_init(&pro,0,10);
    sem_init(&cust,0,0);
    pthread_mutex_init(&m,NULL);
    int i;
    for(i=0;i<5;i++)
    {
        pthread_create(&tid[i],NULL,pro1,(void*)i);
    }
    for(i=0;i<5;i++)
    {
        pthread_create(&tid[i+5],NULL,cust1,(void*)i);
    }
    for(i=0;i<10;i++)
    {
        pthread_join(tid[i],NULL);
    }
    sem_destroy(&pro);
    sem_destroy(&cust);
    pthread_mutex_destroy(&m);
}
