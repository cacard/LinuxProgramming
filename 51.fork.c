//
//	fork/vfork/getpid/getppid
//
//	fork
//		* <0
//		* ==0
//		* >0
//
//	vfork
//		* 不要使用vfork，除非子进程只是立即调用_exit/exec。
//		* 父进程挂起，子进程执行并与父进程共享数据。
//		* 子进程执行完毕退出，或者执行exec后，父进程继续执行。
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

void test_fork()
{
	pid_t temp_pid;
	if((temp_pid=fork())<0){
		perror("error when fork()");
		printf("error wehn fork()..\r\n");
	}
	if(temp_pid==0){
		printf("->child process,pid=%d,ppid=%d\r\n",getpid(),getppid());
	}
	if(temp_pid>0){
		printf("->parent process,pid=%d,ppid=%d\r\n",getpid(),getppid());
	}
}

void test_fork_return_twice()
{
	fork(); // 这里return两次
	printf("@\r\n");//打印两次
}

// 慎重使用vfork
void test_vfork()
{
	pid_t pid;
	int a=1;

	pid=vfork();
	if(pid<0){
		// error
	}
	if(pid==0){
		printf("->child process,pid=%d\r\n",getpid());
		
		for(;a<100;a++){
			printf("a=%d\t",a);
		}
		
		_exit(0);//重要，不要使用exit()，会清理stack
	}
	if(pid>0){
		printf("->parent process,pid=%d\r\n",getpid());
		printf("->a=%d\r\n",a);
	}
}

int main(const int argc,char* argv[])
{
	test_fork_return_twice();
	test_fork();
	test_vfork();
	return 0;
}
