#include <unistd.h>
#include <fcntl.h>
int main()
{
    int fd=open("/dev/pts/2",O_RDWR);
    perror("open");
    write(fd,"hello",5);
    return 0;
}
