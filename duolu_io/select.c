#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main()
{
    struct	sockaddr_in ser,cli;
	int ready;
	int maxfd;
	char ipbuf[20]={0};
	char buf[1024]={0};
	int sfd = socket(AF_INET,SOCK_STREAM,0);
	maxfd=sfd;
	memset(&ser,0,sizeof(ser));
	ser.sin_family=AF_INET;
	ser.sin_port=htons(9000);
	inet_pton(AF_INET,"127.0.0.1",&ser.sin_addr.s_addr);

	if(-1==bind(sfd,(struct sockaddr*)&ser,sizeof(ser)))
		perror("bind");

	if(-1==	listen(sfd,1))
		perror("listen");
	fd_set rset,allset;

	FD_ZERO(&allset);
	FD_SET(sfd,&allset);

	while(1)
	{
		rset=allset;
		ready=select(maxfd+1,&rset,NULL,NULL,NULL);

		if(ready<0)
		{
			perror("select");
			exit(1);
		}
		if(FD_ISSET(sfd,&rset))
		{
			int len = sizeof(cli);
			int fd = accept(sfd,(struct sockaddr*)&cli,&len);
            if(fd==-1)
            {
                perror("accept");
                exit(1);
            }
			printf("ip:%s,port:%d\n",inet_ntop(AF_INET,&cli.sin_addr,ipbuf,sizeof(ipbuf)),ntohs(cli.sin_port));
			FD_SET(fd,&allset);
			FD_CLR(sfd,&rset);
			if(fd>maxfd)
			{
				maxfd=fd;
			}
			ready--;
		}
		int i=0;
		while(ready)
		{
			for(;i<1024;i++)
			{
				if(FD_ISSET(i,&rset))
				{
					break;
				}
			}
			int count = read(i,buf,sizeof(buf));
			if(count <= 0)
			{
				close(i);
				FD_CLR(i,&allset);
			}else
			{
				int j;
				for(j=0;j<count;j++)
				{
					buf[j]=toupper(buf[j]);					
				}
				write(i,buf,count);
			}
			ready--;
			i++;
		}
	}
}
