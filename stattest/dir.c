#include <unistd.h>
#include <dirent.h>
#include <stdio.h>
int main()
{
    DIR *dir= opendir("/home/mage");
    struct dirent *d;

    while((d=readdir(dir))!=NULL)
    {
        if(d->d_name[0]!='.')
            printf("%s\n",d->d_name);
    }
    return 0;
    
}
