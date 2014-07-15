//
//	wait / waitpid
//
//	why?
//		
//
//	僵尸进程：
//	init进程：
//
//
//	how?

#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>

void test_wait()
{
	pid_t pid;
	if((pid=fork())<0){
		// error
	}
	if(pid==0){ // children
		printf("enter children\r\n");
		int i=0;
		for(;i<99999;i++){}
		printf("children exit\r\n");
		exit(0);
	}
	if(pid>0){
		int status;

		printf("->wait()\r\n");
		pid_t pid_wait = wait(&status);
		printf("->child status=%d\r\n",status);

		return;
	}
}

int main()
{
	test_wait();
	return 0;
}

