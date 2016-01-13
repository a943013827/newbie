#include <pthread.h>
#include <stdio.h>

int count;
pthread_mutex_t lock;
void* func(void* argu)
{
	int i;
	int val;
	for(i=0;i<30000;i++)
	{
		pthread_mutex_lock(&lock);
		val=count;
		val++;
		printf("%d\n",val);
		count=val;
		pthread_mutex_unlock(&lock);
	}
	return NULL;
}
int main()
{
	pthread_t tid1,tid2;
	pthread_mutex_init(&lock,NULL);
	pthread_create(&tid1,NULL,func,NULL);
	pthread_create(&tid2,NULL,func,NULL);
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	pthread_mutex_destroy(&lock);
	return 0;
}
