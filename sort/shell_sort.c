#include <stdio.h>

void print(int *a,int len);
void shell_sort(int* a,int len);

int main()
{
    int a[10]={9,8,7,6,5,4,3,2,1,9};
    print(a,10);
    shell_sort(a,10);
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

void shell_sort(int* a,int len)
{
    int i,j,k;
    int gap=len;
    int temp;
    while(gap>1)
    {
        gap=gap/3+1;
        for(i=0;i<gap;i++)
        {
            for(j=i+gap;j<len;j+=gap)
            {
                temp = a[j];
                for(k=j;k>i;k-=gap)
                {
                    if(temp<a[k-gap])
                    {
                        a[k]=a[k-gap];
                    }
                    else
                    {
                        break;
                    }
                }   
                a[k]=temp;
            }
        }
    }
}
