#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

int main()
{
    pid_t pid=fork();
    if(pid==0)
    {
        setsid();
            perror("sid");

        while(1)
        {
            sleep(1);
        }
    }else
    {
        sleep(3);
        wait(NULL);
    }
}
