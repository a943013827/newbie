#include <stdio.h>
#include <string.h>
void dollars(char *dest,char const *src)
{
    int len = strlen(src);
    if(len<3)
    {
        strcpy(dest,"$0.00");
        int i;
        for(i=0;i<len;i++)
        {
            dest[4-i]=src[len-i-1];
        }
    }else
    {
    int count = (len-3)/3;
    int dlen=len+count+2;
    dest[dlen]=0;
    dest[dlen-1]=src[len-1];
    dest[dlen-2]=src[len-2];
    dest[dlen-3]='.';
    int i=dlen-4;
    int j=len-3;
    int k=0;
    while(j>=0)
    {
        dest[i--]=src[j--];
        k++;
        if(k%3==0)
        {
            dest[i--]=',';
        }
    }
    dest[0]='$';
    }
}
int main()
{
    char buf1[1024];
    char buf2[1024];
    scanf("%s",buf2);
    dollars(buf1,buf2);
    printf("%s\n",buf1);
    return 0;
}
