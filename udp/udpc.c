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
	char buf[1024];
	socklen_t len=sizeof(struct sockaddr_in);
	struct sockaddr_in ser,cli;
	
	sfd=socket(AF_INET,SOCK_DGRAM,0);
    perror("socket");
	memset(&ser,0,sizeof(ser));
	memset(&cli,0,sizeof(cli));
	ser.sin_family=AF_INET;
	ser.sin_port=htons(8000);
	inet_pton(AF_INET,"127.0.0.1",&ser.sin_addr.s_addr);
    while(1)
    {
	fgets(buf,sizeof(buf),stdin);
	sendto(sfd,buf,strlen(buf),0,(struct sockaddr*)&ser,len);
    perror("sendto");
	recvfrom(sfd,buf,sizeof(buf),0,NULL,0);
    perror("recvfrom");
	printf("%s",buf);
    }
	close(sfd);
}
