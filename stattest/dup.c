#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
int main()
{
    close(STDOUT_FILENO);
    int fd=open("temp",O_RDWR|O_CREAT,0644);
    perror("open");
    //printf("%d\n",fd);
    write(STDOUT_FILENO,"hello",5);
    printf("printf\n");
    perror("open");
    //close(fd);
    return 0;
}
