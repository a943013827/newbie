#include <unistd.h>
#include <stdio.h>
#include<fcntl.h>
int main()
{
    printf("%d\n",chdir(".."));
    int i;
    printf("%d\n",i= open("/home/mage",O_RDONLY));
    printf("%d\n",fchdir(i));
    char buf1[10]={0};

    while(-1!= read(i,buf1,9))
    {
        int j;
        for(j=0;j<9;j++)
        {printf("%c",buf1[j]);}
    }
    perror("");
    char buf[1024];
    getcwd(buf,1024);
    printf("%s\n",buf);
    return 0;
}
