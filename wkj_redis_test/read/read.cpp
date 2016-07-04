#include "hiredis.h"
#include <stdio.h>
#include <string>
#include <iostream>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
using namespace std;

void* work_thread(void* p)
{
    int num=(int)p;
    char name[10]={0};
    sprintf(name,"%d",num);
    FILE* f=fopen(name,"w");
    std::string ip;
    int port;
    redisReply* reply;
    redisContext* context;
    ip="127.0.0.1";
    port=6379;
    context = redisConnect(ip.data(),port);
    if(context->err)
    {
        redisFree(context);
        printf("connect to redis faile\n");
        return NULL;
    }
    //printf("connect success\n");
    int i;
    for(i=0;i<10000;i++)
    {
        int randnum;
        char buf[100]={0};
        sprintf(buf,"GET namename%d",randnum=rand()%1000000);
        reply=(redisReply*)redisCommand(context,buf);
        if(reply==NULL||reply->type == REDIS_REPLY_ERROR)
        {
            printf("exe command fail\n");
            continue;
        }
        if(reply->type == REDIS_REPLY_NIL || reply->str == NULL){
            printf("key not exits\n");
            continue;
        }
        char buf2[15]={0};
        sprintf(buf2,"namename%d\n",randnum);
        fputs(buf2,f);
        fputs(reply->str,f);
        fputs("\n",f);
        freeReplyObject(reply);
    }
    fclose(f);
    redisFree(context);
    return NULL;
}


int main()
{
    srand(time(NULL));
    pthread_t tid[100];
    int i=0;
    for(i=0;i<100;i++)
        pthread_create(&tid[i],NULL,work_thread,(void*)i);
    for(i=0;i<100;i++)
        pthread_join(tid[i],NULL);
    return 0;
}

