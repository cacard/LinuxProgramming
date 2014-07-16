//
//	pipe demo
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void test_pipe()
{
	int fds[2];
	if(pipe(fds) !=0 ){
		perror("error when create pipe");
		return;
	}

	int r=fork();
	if(r<0){
		perror("error when fork()");
		return;
	}
	if(r==0){
		printf("->child\r\n");
		sleep(3);

		if(close(fds[0])!=0){
		}

		// write msg
		char* msg="hello";
		int r2=write(fds[1],msg,strlen(msg));
		// close
		if(close(fds[1])!=0){
			perror("error when close fds[1]");
		}

		sleep(5);
		printf("->exit child\r\n");
		exit(0);
	}
	if(r>0){

		// read
		int bufsize=10;
		char buf[bufsize];
		int n=0;
		if((n=read(fds[0],buf,bufsize)) >0 ){
			printf("->%s,and n=%d\r\n",buf,n);
		}
		if(n==0){
			printf("end.\r\n");
		}
		if(n<0){
			perror("error when read file");
		}

		waitpid(r,NULL,0); // blocking for waiting child exit

		printf("->exit father process\r\n");
		return;
	}
}

int main(int argc,char* argv[])
{
	test_pipe();
	return 0;
}
