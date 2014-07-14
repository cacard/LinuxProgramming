//
//	wait / waitpid
//
//	why?
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
	if((pid==fork())<0){
		// error
	}
	if(pid==0){ // children
		exit(0);
	}

	int status;
	pid_t pid_wait = wait(&status);
}

int main()
{

	return 0;
}

