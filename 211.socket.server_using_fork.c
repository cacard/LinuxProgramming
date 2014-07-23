//
//	使用fork实现多进程并发服务器
//
//
//	测试时，client 使用 socket.demo.c
//
//	TODO waitpid

#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <string.h> // bzero

void start_server()
{
	// create server socket address
	struct sockaddr_in server_sock_addr;
	bzero(&server_sock_addr,sizeof(server_sock_addr));
	server_sock_addr.sin_family=AF_INET;
	server_sock_addr.sin_port=90;
	server_sock_addr.sin_addr.s_addr=inet_addr("127.0.0.1");

	// socket()
	int server_socket_fd=socket(AF_INET,SOCK_STREAM,0);
	if(server_socket_fd<0){
		perror("->server:error when socket()");
		return;
	}else{
		printf("->server socket() ok.\r\n");
	}

	// bind()
	int r_bind=bind(server_socket_fd,(struct sockaddr*)&server_sock_addr,sizeof(server_sock_addr));
	if(r_bind<0){
		perror("->server:error when bind()");
		return;
	}else{
		printf("->server bind() ok\r\n");
	}

	// listen()
	int r_listen=listen(server_socket_fd,10);
	if(r_listen<0){
		perror("->server:error when listen()");
	}else{
		printf("->server listen() ok.\r\n");
	}

	// accept
	struct sockaddr client_socket_addr;
	int client_socket_addr_len;
	while(1==1){
		printf("->server:accepting...\r\n");
		int client_fd=accept(server_socket_fd,(struct sockaddr*)&client_socket_addr,&client_socket_addr_len);
		if(client_fd==-1){
			perror("->server:error when accept");
			continue;
		}else{
			printf("->server accepted ok\r\n");
		}

		// fork
		int pid=fork();
		if(pid<0){
			perror("->server:error when fork");
			exit(0); // do not continue
		}
		if(pid==0){
			printf("child process,pid==%d\r\n",getpid());
			// child
			close(server_socket_fd);
			// ...
			printf("hello\r\n");
			close(client_fd);
			exit(0);
		}
		if(pid>0){
			// parent
			close(client_fd);
		}

	}
}

int main(int argc,char* argv[])
{
	start_server();
	return 0;
}
