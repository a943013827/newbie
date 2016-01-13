#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <signal.h>


#define SIZE 10
#define STEP 10
typedef struct task
{
    void* (*func)(void*);
    void* arg;
}task;

typedef struct threadpool
{
    pthread_mutex_t lock;
    pthread_mutex_t lock2;
    pthread_cond_t taskfull;
    pthread_cond_t taskempty;
    pthread_t *threads;
    pthread_t tid;
    task *tasks;
    int min_thr_num;
    int max_thr_num;
    int live_thr_num;
    int busy_thr_num;
    int exit_thr_num;
    int head;
    int tail;
    int size;
    int max_size;
    int stat;
}threadpool;

int pool_free(threadpool* tp);
int is_thread_alive(pthread_t tid);
void* mgrthread(void* p);
void* thread(void* p)
{
    threadpool* tp = (threadpool*)p;
    task t;
    while(1)
    {
        pthread_mutex_lock(&tp->lock);
        if(tp->exit_thr_num>0)
        {
            (tp->live_thr_num)--;
            (tp->exit_thr_num)--;
            pthread_mutex_unlock(&tp->lock);
            pthread_exit(NULL);
        }
        while(tp->size==0)
        {
            pthread_cond_wait(&tp->taskempty,&tp->lock);
        }
        if(tp->exit_thr_num>0)
        {
            (tp->live_thr_num)--;
            (tp->exit_thr_num)--;
            pthread_mutex_unlock(&tp->lock);
            pthread_exit(NULL);
        }
        t=tp->tasks[tp->head];
        tp->head=(tp->head+1)%tp->size;
        (tp->size)--;
        (tp->busy_thr_num)++;
        pthread_mutex_unlock(&tp->lock);
        pthread_cond_signal(&tp->taskfull);
        (t.func)(t.arg);
        pthread_mutex_lock(&tp->lock2);
        (tp->busy_thr_num)--;
        pthread_mutex_unlock(&tp->lock2);

    }
}

threadpool* pool_create(int min_thr_num,int max_thr_num,int max_size)
{
    threadpool* tp=(threadpool*)malloc(sizeof(threadpool));
    pthread_mutex_init(&tp->lock,NULL);
    pthread_mutex_init(&tp->lock2,NULL);
    pthread_cond_init(&tp->taskfull,NULL);
    pthread_cond_init(&tp->taskempty,NULL);
    tp->threads=(pthread_t*)malloc(sizeof(pthread_t)*max_thr_num);
    memset(tp->threads,0,sizeof(pthread_t)*max_thr_num);
    tp->tasks=(task*)malloc(sizeof(task)*max_size);
    tp->min_thr_num=min_thr_num;
    tp->max_thr_num=max_thr_num;
    tp->live_thr_num=min_thr_num;
    tp->busy_thr_num=0;
    tp->exit_thr_num=0;
    tp->head=0;
    tp->tail=0;
    tp->size=0;
    tp->max_size=max_size;
    tp->stat=0;

    pthread_mutex_lock(&tp->lock);
    pthread_create(&tp->tid,NULL,mgrthread,(void*)tp);
    int i;
    for(i=0;i<min_thr_num;i++)
    {
        pthread_create(&(tp->threads[i]),NULL,thread,(void*)tp);
        pthread_detach(tp->threads[i]);
    }
    pthread_mutex_unlock(&tp->lock);
    return tp;
}

int pool_add(threadpool* tp,void*(*func)(void*),void*arg)
{
    if(tp->stat==1)
        return -1;
    pthread_mutex_lock(&tp->lock);
    while(tp->size==tp->max_size)
        pthread_cond_wait(&tp->taskfull,&tp->lock);
    tp->tasks[tp->tail].func=func;
    tp->tasks[tp->tail].arg=arg;
    tp->tail=(tp->tail+1)%tp->max_size;
    (tp->size)++;
    pthread_cond_signal(&tp->taskempty);
    pthread_mutex_unlock(&tp->lock);
    return 0;
}

void* mgrthread(void* p)
{
    threadpool* tp= (threadpool*)p;
    while(1)
    {
        sleep(10);
        pthread_mutex_lock(&tp->lock);
        if(tp->stat==1)
        {
            tp->exit_thr_num=tp->live_thr_num;
            int count = tp->max_thr_num;
            pthread_mutex_unlock(&tp->lock);
            pthread_cond_broadcast(&tp->taskempty);
            int i;
            while(1)
            {
                int flag = 0;
                for(i=0;i<count;i++)
                {
                    if(tp->threads[i]!=0&&is_thread_alive(tp->threads[i])==1)
                    {
                        flag=1;
                        break;
                    }
                }
                if(flag==0)
                    break;
            }
            pool_free(tp);
            pthread_exit(NULL);
        }else
        {
            if(tp->size>SIZE&&tp->live_thr_num<tp->max_thr_num)
            {
                int i;
                int count;
                for(i=0,count=0;i<tp->max_thr_num,count<STEP;i++)
                {
                    if(tp->threads[i]==0||is_thread_alive(tp->threads[i])==0)
                    {
                        pthread_create(&(tp->threads[i]),NULL,thread,(void*)tp);
                        pthread_detach(tp->threads[i]);
                        count++;
                    }
                }
                pthread_mutex_unlock(&tp->lock);
            }
            if(tp->live_thr_num > tp->busy_thr_num*2&&tp->live_thr_num > tp->min_thr_num)
            {
                int n = (tp->live_thr_num - tp->min_thr_num) > tp->busy_thr_num ? tp->busy_thr_num:(tp->live_thr_num - tp->min_thr_num);
                n = STEP > n?n:STEP;
                tp->exit_thr_num = n;
                int i;
                for(i=0;i<n;i++)
                {
                    pthread_cond_signal(&tp->taskempty);
                }
                pthread_mutex_unlock(&tp->lock);
            }
        }
    }
}

int pool_free(threadpool* tp)
{
    pthread_mutex_destroy(&tp->lock);
    pthread_mutex_destroy(&tp->lock2);
    pthread_cond_destroy(&tp->taskfull);
    pthread_cond_destroy(&tp->taskempty);
    free(tp->threads);
    free(tp->tasks);
    free(tp);
}

int is_thread_alive(pthread_t tid)
{
    if(pthread_kill(tid,0)==ESRCH)
        return 0;
    else
        return 1;
}

void pool_destroy(threadpool* tp)
{
    pthread_t tid=tp->tid;
    tp->stat=1;
    pthread_join(tid,NULL);
}
void *process(void *arg)
{
    printf("thread 0x%x working on task %d\n ",(unsigned int)pthread_self(),*(int *)arg);
    sleep(1);
    printf("task %d is end\n",*(int *)arg);
    return NULL;
}
int main()
{
    threadpool* p=pool_create(3,100,100);
    int num[20]={0};
    int i;
    for(i=0;i<20;i++)
    {
        num[i]=i;
        pool_add(p,process,(void*)&num[i]);
    }
    pool_destroy(p);
}
