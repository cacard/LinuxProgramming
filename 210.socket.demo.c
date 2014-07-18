//
//	socket functions
//
//	server
//		- fd_server=socket(af,type,proto)
//		- bind(fd,sockaddr*,sizeof())
//		- listen(fd,backlog) 主动到被动
//		- accept(fd,sockaddr*,addr_len*) 阻塞
//			- read/write
//		- close()
//
//	client
//		- socket()
//		- connect()
//			- read/write
//		- close()

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <pthread.h>

char* SERVER_IP="127.0.0.1";
const int PORT=90;

// thread for socket server
void* thread_server()
{
	printf("->thread_server runing\r\n");

	// create socket
	int fdServer = socket(AF_INET,SOCK_STREAM,0);
	if(fdServer<0){
		perror("error when create socket server");
		return NULL;
	}else{
		printf("->server socket() ok.\r\n");
	}

	// bind
	struct sockaddr_in serverSockAddr;
	struct in_addr ip;
	ip.s_addr=inet_addr(SERVER_IP);
	serverSockAddr.sin_family=AF_INET;
	serverSockAddr.sin_port=PORT;
	serverSockAddr.sin_addr=ip;

	if(bind(fdServer,(struct sockaddr*)&serverSockAddr,sizeof(serverSockAddr))<0)
	{
		perror("error when server socket bind()");
	}else{
		printf("->server bind() ok.\r\n");
	}

	// listen
	if(listen(fdServer,SOMAXCONN/*backlog*/)<0){
		perror("error when server socket listen");
		return NULL;
	}else{
		printf("->server listen() ok.\r\n");
	}

	// accept
	struct sockaddr clientSockAddr;
	int clientSockAddrLen;
	while(1==1){
		printf("->server accepting...\r\n");
		int fdClient=accept(fdServer,&clientSockAddr,&clientSockAddrLen);
		if(fdClient<0){
			perror("error when accept");
			continue;
		}

		printf("-> server accept() ok.\r\n");
	}
}

// thread socket client
void* thread_client()
{
	printf("->thread_client start running\r\n");

	//create socket
	int fdClient = socket(AF_INET,SOCK_STREAM,0);
	if(fdClient<0){
		perror("error when create socket for client");
		return NULL;
	}else{
		printf("->client socket() ok.\r\n");
	}

	// connect
	struct sockaddr_in serverSockAddr;
	struct in_addr ip;
	ip.s_addr=inet_addr(SERVER_IP);
	serverSockAddr.sin_family=AF_INET;
	serverSockAddr.sin_port=PORT;
	serverSockAddr.sin_addr=ip;

	if(connect(fdClient,(struct sockaddr*)&serverSockAddr,sizeof(serverSockAddr))<0)
	{
		perror("error when connect to server");
	}else{
		printf("->client connect() ok.\r\n");
	}

	// close
	if(close(fdClient)!=0){
		perror("error when close client socket fd");
	}else{
		printf("->client close() ok.\r\n");
	}

	return NULL;
}

void start_running()
{
	pthread_t tidServer;
	pthread_t tidClient;
	int r1,r2;
	r1=pthread_create(&tidServer,NULL,thread_server,NULL);

	// sleep for server runing
	sleep(3);

	r2=pthread_create(&tidClient,NULL,thread_client,NULL);
	if(r1!=0){
		perror("error when create thread_server");
	}else{
		pthread_join(tidServer,NULL);
	}
	if(r2!=0){
		perror("error when create thread_client");
	}else{
		pthread_join(tidClient,NULL);
	}
}

int main(int argc,char* argv[])
{
	start_running();
	return 0;
}
