//
//	socket functions
//
//	server
//		- socket(af,type,proto)
//		- [bind()]
//		- listen(fd,backlog) 主动到被动
//		- accept(fd,sockaddr*,addr_len*) 阻塞
//
//	client
//		- socket()
//		- connect()
//	

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <pthread.h>

// thread for socket server
void* thread_server()
{
	// create socket
	int fdServer = socket(AF_INET,SOCK_STREAM,0);
	if(fdServer<0){
		perror("error when create socket server");
		return NULL;
	}

	// listen
	if(listen(fdServer,SOMAXCONN/*backlog*/)<0){
		perror("error when server socket listen");
		return NULL;
	}

	// accept
}

// thread socket client
void* thread_client()
{

}

void start_running()
{
}

int main(int argc,char* argv[])
{

	return 0;
}
