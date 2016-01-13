#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <string.h>
#include <strings.h>

int main()
{
	int sfd;
	char buf[2];
	socklen_t len=sizeof(struct sockaddr_in);
	struct sockaddr_in ser,cli;
	
	sfd=socket(AF_INET,SOCK_DGRAM,0);
    perror("socket");
	memset(&ser,0,sizeof(ser));
	memset(&cli,0,sizeof(cli));
	ser.sin_family=AF_INET;
	ser.sin_port=htons(8000);
	inet_pton(AF_INET,"127.0.0.1",&ser.sin_addr.s_addr);

	bind(sfd,(struct sockaddr*)&ser,sizeof(ser));
    perror("bind");
	read(STDIN_FILENO,buf,sizeof(buf));
	while(1)
	{
	int count = 0;
	count = recvfrom(sfd,buf,sizeof(buf),0,(struct sockaddr*)&cli,&len);
    perror("recvfrom");
	int i;
	for(i=0;i<count;i++)
		buf[i]=toupper(buf[i]);
    buf[i]=0;
    printf("%s\n",buf);
	sendto(sfd,buf,count,0,(struct sockaddr*)&cli,len);
    perror("sendto");
	}
	close(sfd);
}
