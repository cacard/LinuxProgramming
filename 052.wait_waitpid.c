//
//	wait / waitpid
//
//	why?
//	子进程结束后需要通知父进程，反馈自己的状态
//	父进程释放子进程资源。
//
//	how?
//	pid_t wait(int* status);
//
//	pid_t waitpid(pid_t waitfor,int* status,int option);
//		- 可选择等待哪些子进程
//		- 可不阻塞等待
//
//	孤儿进程
//
//
//	僵尸进程
//
//

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
		printf("enter children,will sleep(3)\r\n");
		sleep(3);
		printf("children exit\r\n");
		exit(0);
	}
	if(pid>0){ // father
		int status;

		printf("->wait()\r\n");
		pid_t pid_wait = wait(&status);
		printf("->child status=%d\r\n",status);

		return;
	}
}

void test_wait_pid()
{
	pid_t pid;
	if((pid=fork())<0){
		perror("error when fork()");
	}
	if(pid==0){
		sleep(3);
		exit(0);
	}
	
	int status;
	pid_t r=waitpid(pid,&status,0);
	printf("->(father) return pid is %d,status is %d",r,status);

}

int main()
{
	test_wait();
	test_wait_pid();
	return 0;
}

