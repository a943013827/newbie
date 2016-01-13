#include <stdio.h>
int mystrlen(char* s);
void mystrcat(char* s1,char*s2);
int myatoi(char* s);
float myatof(char* s);
int main(void)
{
    char c[]="-123.1234";
    printf("%f\n",myatof(c));

    return 0;
}
int mystrlen(char* s)
{
    int i=0;
    while(*s)
    {
        i++;
        s++;
    }
    return i;
}

void mystrcat(char* s1,char*s2)
{
    int i =0;
    i=mystrlen(s1);
    while(*s2)
    {
        *(s1+i)=*s2;
        i++;
        s2++;
    }
}
int myatoi(char* s)
{
    int n;
    if(*s!='-')
    {
        n =mystrlen(s);
        int i,x=0,y=0;
        for(i=0;i<n;i++)
        {
            y=*s-'0';
            x=10*x+y;
            s++;
        }
        return x;
    }
    else
    {
        n = mystrlen(s)-1;
        int i,x=0,y=0;
        s++;
        for(i=0;i<n;i++)
        {
            y=*s-'0';
            x=10*x+y;
            s++;
        }
        return -x;
    }



}


float myatof(char* s)
{
    int n=0,m=0,i=0,x=0;
    float z=0,y=0;
    if(*s!='-')
    {
        while(s[n]!='.')
            n++;
        for(i=0;i<n;i++)
        {
            y=s[i]-'0';
            x=10*x+y;
        }

        m=n+1;
        while(s[m])
            m++;

         for(i=0;i<m-n-1;i++)
         {
             y=s[m-1-i]-'0';
             z=z/10+y/10;
         }
         return x+z;
    }
    else
    {
        s++;
        while(s[n]!='.')
            n++;
        for(i=0;i<n;i++)
        {
            y=s[i]-'0';
            x=10*x+y;
        }

        m=n+1;
        while(s[m])
            m++;

         for(i=0;i<m-n-1;i++)
         {
             y=s[m-1-i]-'0';
             z=z/10+y/10;
         }
         return (float)-(x+z);
    }

}

