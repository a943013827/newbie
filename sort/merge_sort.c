#include <stdio.h>

void print(int*, int);
void merge(int* arr1,int len1,int* arr2,int len2,int* res);
void merge_sort(int*,int,int,int*);

int main()
{
    int a[10]={9,8,7,6,5,4,3,2,1,9};
    int res[10]={0};
    merge_sort(a,3,7,res);
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

void merge(int* arr1,int len1,int* arr2,int len2,int *res)
{
    int i=0,j=0;
    while(i<len1&&j<len2)
    {
        if(arr1[i]<arr2[j])
        {
            *res++=arr1[i++];
        }
        else
        {
            *res++=arr2[j++];
        }
    }
    while(i<len1)
    {
        *res++=arr1[i++];
    }
    while(j<len2)
    {
        *res++=arr2[j++];
    }
    return;
}

void merge_sort(int* arr,int start,int end, int* res)
{
    if(start>=end)
        return;
    int mid = (start+end)/2;
    merge_sort(arr,start,mid,res);
    merge_sort(arr,mid+1,end,res);
    merge(arr+start,mid-start+1,arr+mid+1,end-mid,res+start);
    int i;
    for(i=start;i<=end;i++)
    {
        arr[i]=res[i];
    }
}

