#include <stdlib.h>
#include <pthread.h>
#include <stdio.h>
#include <semaphore.h>

int queue[5];
sem_t blank_number,product_number;

void* producer(void* arg)
{
	int p = 0;
	while(1)
	{
		sem_wait(&blank_number);
		queue[p]=rand()%100;
		printf("producer%d\n",queue[p]);
		sem_post(&product_number);
		p=(p+1)%5;
		sleep(rand()%5);
	}
}

void* consumer(void* arg)
{
	int p=0;
	while(1)
	{
	sem_wait(&product_number);
	printf("consumer%d\n",queue[p]);
	queue[p]=0;
	sem_post(&blank_number);
	p=(p+1)%5;
	sleep(rand()%5);
	}
}

int main()
{
	pthread_t tid1,tid2;
	sem_init(&blank_number,0,5);
	sem_init(&product_number,0,0);
	pthread_create(&tid1,NULL,producer,NULL);
	pthread_create(&tid2,NULL,consumer,NULL);
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	sem_destroy(&blank_number);
	sem_destroy(&product_number);
	return 0;

}
