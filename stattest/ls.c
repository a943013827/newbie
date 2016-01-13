#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>
int isdir(const char *s)
{
    struct stat st;
    if(lstat(s,&st)==-1)
    {
        printf("stat error");
        return 0;
    } 
    return S_ISDIR(st.st_mode);
}

void printde(const char * s)
{
    struct stat st;
    if(stat(s,&st)==-1)
        return;
    else
        printf("%8ld %s\n",st.st_size,s);
}

void ls(const char *s)
{
    DIR *d;
    if((d=opendir(s))==NULL)
    {
        printf("can't open dir");
        return;
    }
    struct dirent *de;
    while((de=readdir(d))!=NULL)
    {

        if(!strcmp(de->d_name,".")||!strcmp(de->d_name,".."))
            continue;
        char name[1024]={0};
        strcpy(name,s);
        strcat(name,"/");
        strcat(name,de->d_name);
        if(isdir(name))
        {
            ls(name);
        }
        else
        {
            printde(name);
        } 
    }
}
int main(int argc,char **argv)
{
    if(argc==1)
    {
        ls(".");
    }
    else if(argc>1)
    {
        int i=1;
        while(argc>1)
        {
            ls(argv[i]);
            i++;
            argc--;
        }
    }
    return 0;
}
