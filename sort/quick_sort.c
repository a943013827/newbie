#include <stdio.h>

void print(int*, int);
void qsort(int*, int*);

int main()
{
    int a[10]={9,8,7,6,5,4,3,2,1,9};
    qsort(a,a+9);
    print(a,10);
}

void print(int* a,int len)
{
    int i;
    for(i=0;i<len;i++)
    {
        printf("%d",a[i]);
    }
    printf("\n");
}

void qsort(int* start,int *end)
{
    int* head=start;
    int* tail=end;
    if(head>=tail)
        return;
    int temp = *head;
    while(head<tail)
    {
        while(*tail>=temp&&head<tail)
            tail--;
        *head=*tail;
        while(*head<=temp&&head<tail)
            head++;
        *tail=*head;
    }
    *head=temp;
    qsort(start,head-1);
    qsort(head+1,end);
}
