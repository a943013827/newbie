#include <unistd.h>
#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <stdio.h>


pthread_mutex_t m[5];

void* eat(void* p)
{
    usleep(rand()%2000000);
    int num =(int)p;
    int ret1,ret2;
    while(1)
    {
tab1:
        sleep(rand()%5);
        if((ret1=pthread_mutex_trylock(&m[num]))==EBUSY)
        {
            goto tab1;
        }
        printf("%c fetches left chopstick %d \n",'A'+num,num);
        int i =0;
        usleep(100000);
tab2:   if(i<3&&(ret2=pthread_mutex_trylock(&m[(num+1)%5]))==EBUSY)
        {
            i++;
            goto tab2; 
        }else if(i==3)
        {
            pthread_mutex_unlock(&m[num]);
            goto tab1;
        }
        printf("%c fetches right chopstick %d \n",'A'+num,(num+1)%5);
        if(ret1==0&&ret2==0)
        {
            printf("%c eating\n",'A'+num);
            pthread_mutex_unlock(&m[num]);
            pthread_mutex_unlock(&m[(num+1)%5]);
            printf("%c release chopsticks %d %d\n",'A'+num,num,(num+1)%5);
            sleep(rand()%3);
        }else
        {
            printf("unknow error");
            break;
        }
    }
}

int main()
{
    int i;
    srand(time(NULL));
    pthread_t tid[5];
    for(i=0;i<5;i++)
    {
        pthread_mutex_init(&m[i],NULL);
    }
    for(i=0;i<5;i++)
    {
        pthread_create(&tid[i],NULL,eat,(void*)i);
    }
    for(i=0;i<5;i++)
    {
        pthread_join(tid[i],NULL);
    }
    for(i=0;i<5;i++)
    {
        pthread_mutex_destroy(&m[i]);
    }
    return 0;
}
