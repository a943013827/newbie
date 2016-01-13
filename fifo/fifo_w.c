#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
int main()
{
//	int ret	= mkfifo("myfifo",0644);
//	if(ret==-1)
//	{
//		perror("mkfifo");
//		return -1;
//	}
	int fd=open("myfifo",O_RDWR);
	char buf[1024]={0};
	int i=0;
	while(1)
	{
		sprintf(buf,"hello_%d",i);
		write(fd,buf,1024);
        printf("%s\n",buf);
		i++;
		sleep(3);
	}
	close(fd);
}
