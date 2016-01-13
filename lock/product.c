#include <stdlib.c>
#include <stdio.h>
#include <pthread.h>

struct msg
{
	struct msg * next;
	int i;
}

struct msg *head;

pthread_cond_t ready = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void * consumer(void* p)
{
	struct msg * temp;
	while(1)
	{
		pthread_mutex_lock(&lock);
		while(head==NULL)
			pthread_cond_wait(&ready,&lock);
		temp=head;
		head=head->next;
		pthread_mutex_unlock(&lock);
		printf("conxumer %d",temp->i);
		free(temp);
		sleep(rand()%5);
	}
}

void * producer(void*p)
{
	struct msg* temp;
	while(1)
	{
		temp=malloc(sizeof(struct msg));
		temp->i=rand()%100;
		pthread_mutex_lock(&lock);
		temp->next=head;
		head=temp;
		printf("producer %d",temp->i);
		pthread_mutex_unlock(&lock);
		pthread_cond_signal(&ready);
		sleep(rand()%5);
	}
}
int main()
{
	pthread_t tid1,tid2;
	srand(time(NULL));
	pthread_create(&tid1,NULL)
}
