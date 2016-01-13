#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
int main(int argc , char * args[])
{
    if(argc!=2)
        exit(1);
   struct stat s;
    if(lstat(args[1],&s)==-1)
    {
        perror("stat");
        exit(1);
    }
    printf("%s\n",args[1]);
    if(S_ISREG(s.st_mode))
    {
        printf("regular file\n");
    }else if(S_ISDIR(s.st_mode))
    {
        printf("directory\n");
    }else if(S_ISCHR(s.st_mode))
    {
        printf("charactor device\n");
    }else if(S_ISBLK(s.st_mode))
    {
        printf("block device\n");
    }else if(S_ISLNK(s.st_mode))
    {
        printf("soft  link file\n");
    }

    return 0;
}
