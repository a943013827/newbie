#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/socket.h>
#include <resolv.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <openssl/ssl.h>
#include <openssl/err.h>
#include <pthread.h>
#define MAXBUF 1024

static pthread_mutex_t *lockarray;
pthread_mutex_t m;
static void lock_callback(int mode, int type, const char *file, int line)
{
	(void)file;
	(void)line;
	if (mode & CRYPTO_LOCK) {
		pthread_mutex_lock(&(lockarray[type]));
	}
	else {
		pthread_mutex_unlock(&(lockarray[type]));
	}
}

static unsigned long thread_id(void)
{
	unsigned long ret;

	ret=(unsigned long)pthread_self();
	return(ret);
}

static void init_locks(void)
{
	int i;

	lockarray=(pthread_mutex_t *)OPENSSL_malloc(CRYPTO_num_locks() *
			sizeof(pthread_mutex_t));
	for (i=0; i<CRYPTO_num_locks(); i++) {
		pthread_mutex_init(&(lockarray[i]),NULL);
	}
	pthread_mutex_init(&m,NULL);
	CRYPTO_set_id_callback(thread_id);
	CRYPTO_set_locking_callback(lock_callback);
}

static void kill_locks(void)
{
	int i;

	CRYPTO_set_locking_callback(NULL);
	for (i=0; i<CRYPTO_num_locks(); i++)
		pthread_mutex_destroy(&(lockarray[i]));
	pthread_mutex_destroy(&m);
	OPENSSL_free(lockarray);
}


void ShowCerts(SSL * ssl)
{
	X509 *cert;
	char *line;

	cert = SSL_get_peer_certificate(ssl);
	if (cert != NULL) {
		printf("数字证书信息:\n");
		line = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);
		printf("证书: %s\n", line);
		free(line);
		line = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0);
		printf("颁发者: %s\n", line);
		free(line);
		X509_free(cert);
	} else
		printf("无证书信息！\n");
}
/************关于本文档********************************************
 *filename: ssl-client.c
 *purpose: 演示利用 OpenSSL 库进行基于 IP层的 SSL 加密通讯的方法，这是客户端例子
 *wrote by: zhoulifa(zhoulifa@163.com) 周立发(http://zhoulifa.bokee.com)
 Linux爱好者 Linux知识传播者 SOHO族 开发者 最擅长C语言
 *date time:2007-02-02 20:10
 *Note: 任何人可以任意复制代码并运用这些文档，当然包括你的商业用途
 * 但请遵循GPL
 *Thanks to:Google
 *Hope:希望越来越多的人贡献自己的力量，为科学技术发展出力
 * 科技站在巨人的肩膀上进步更快！感谢有开源前辈的贡献！
 *********************************************************************/

struct ipport{
	char * ip;
	char* port;
	int thread_num;
};

void* thread_ssl(void *p)
{
	struct ipport* pp=(struct ipport*)p;
	int sockfd, len;
	struct sockaddr_in dest;
	char buffer[MAXBUF + 1];
	SSL_CTX *ctx;
	SSL *ssl;

	/* SSL 库初始化，参看 ssl-server.c 代码 */
	//pthread_mutex_lock(&m);
	//SSL_library_init();
	//OpenSSL_add_all_algorithms();
	//SSL_load_error_strings();
	//pthread_mutex_unlock(&m);
	ctx = SSL_CTX_new(TLSv1_client_method());//TSL协议
	if (ctx == NULL) {
		ERR_print_errors_fp(stdout);
		exit(1);
	}

	/* 创建一个 socket 用于 tcp 通信 */
	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
		perror("Socket");
		exit(errno);
	}
	printf("socket created\n");

	/* 初始化服务器端（对方）的地址和端口信息 */
	bzero(&dest, sizeof(dest));
	dest.sin_family = AF_INET;
	dest.sin_port = htons(atoi(pp->port));
	if (inet_aton(pp->ip, (struct in_addr *) &dest.sin_addr.s_addr) == 0) {
		perror(pp->ip);
		exit(errno);
	}
	printf("address created\n");

	/* 连接服务器 */
	if (connect(sockfd, (struct sockaddr *) &dest, sizeof(dest)) != 0) {
		perror("Connect ");
		exit(errno);
	}
	printf("server connected\n");

	/* 基于 ctx 产生一个新的 SSL */
	ssl = SSL_new(ctx);
	SSL_set_fd(ssl, sockfd);
	/* 建立 SSL 连接 */
	if (SSL_connect(ssl) == -1)
		ERR_print_errors_fp(stderr);
	else {
		printf("Connected with %s encryption\n", SSL_get_cipher(ssl));
		ShowCerts(ssl);
	}

	/* 接收对方发过来的消息，最多接收 MAXBUF 个字节 */
	bzero(buffer, MAXBUF + 1);
	/* 接收服务器来的消息 */
	len = SSL_read(ssl, buffer, MAXBUF);
	if (len > 0)
		printf("%d号线程 接收消息成功:'%s'，共%d个字节的数据\n",
				pp->thread_num,buffer, len);
	else {
		printf
			("消息接收失败！错误代码是%d，错误信息是'%s'\n",
			 errno, strerror(errno));
		goto finish;
	}
	bzero(buffer, MAXBUF + 1);
	strcpy(buffer, "from client->server");
	/* 发消息给服务器 */
	len = SSL_write(ssl, buffer, strlen(buffer));
	if (len < 0)
		printf
			("消息'%s'发送失败！错误代码是%d，错误信息是'%s'\n",
			 buffer, errno, strerror(errno));
	else
		printf("%d号线程 消息'%s'发送成功，共发送了%d个字节！\n",
				pp->thread_num,buffer, len);

finish:
	/* 关闭连接 */
	SSL_shutdown(ssl);
	SSL_free(ssl);
	close(sockfd);
	SSL_CTX_free(ctx);
	return NULL;
}

int main(int argc,char* argv[])
{
	if(argc !=3)
	{
		printf("参数格式错误！正确用法如下：\n\t\t%s IP地址 端口\n\t比如:\t%s 127.0.0.1 80\n此程序用来从某个 IP 地址的服务器某个端口接收最多 MAXBUF 个字节的消息",argv[0], argv[0]);
		exit(0);
	}

	SSL_library_init();
	OpenSSL_add_all_algorithms();
	SSL_load_error_strings();
	init_locks();
	pthread_t pid[50];
	struct ipport pp[50];
	int i=0;
	for(i=0;i<50;i++)
	{
		pp[i].ip=argv[1];
		pp[i].port=argv[2];
		pp[i].thread_num=i;
		pthread_create(&pid[i],NULL,thread_ssl,(void*)&pp[i]);
	}
	for(i=0;i<50;i++)
	{
		pthread_join(pid[i],NULL);
	}
	//printf("%d\n",open("test",O_RDWR|O_CREAT,0644));
	kill_locks();
	return 0;
}
