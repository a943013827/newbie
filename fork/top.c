#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
int main()
{
    int fd = open("top.txt",O_RDWR|O_CREAT|O_TRUNC,0644);
    if(fd==-1)
    {
        perror("");
        exit(1);
    }
   if(-1 == dup2(fd,STDOUT_FILENO))
   {
       perror("");
       exit(1);
   }
   char * s[]={"ps","aux",NULL};
    execvp("ps",s);
    perror("");
    exit(1);
}
