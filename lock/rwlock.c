#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

int count;

pthread_rwlock_t lock;
void * mywrite(void * argu)
{
	while(1)
	{
		pthread_rwlock_wrlock(&lock);
		printf("%d ",count);
		count++;
		printf("write %d--- %d\n",(int)argu,count);
		pthread_rwlock_unlock(&lock);
	//	usleep(1000);
	}
}

void* myread(void * argu)
{
	while(1)
	{
		pthread_rwlock_rdlock(&lock);
		printf("read %d---- %d\n",(int)argu,count);
	//	usleep(100000);
		pthread_rwlock_unlock(&lock);
	}
}

int main()
{
	pthread_t tid[8];
	pthread_rwlock_init(&lock,NULL);
	int i;
	for(i=0;i<3;i++)
	{
		pthread_create(&tid[i],NULL,myread,(void*)i);
	}
	for(i=0;i<5;i++)
	{
		pthread_create(&tid[i+5],NULL,mywrite,(void*)i);
	}
	for(i=0;i<8;i++)
	{
		pthread_join(tid[i],NULL);
	}
	pthread_rwlock_destroy(&lock);
	return 0;
}
