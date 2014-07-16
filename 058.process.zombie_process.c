//
//	僵尸进程
//		zombie-process
//		进程退出后，其task_struce依然存在未释放，此种进程即为Zombie
//		ps状态为Z
//
//	如何产生的？
//		子进程退出后，不会释放其task_struct，因为父进程需要通过该struct读取子进程退出码。
//		父进程调用wait/waitpid读取task_struct退出码后，释放子进程的task_struct。
//		如果父进程没有调用wait/waitpid，且父进程在子进程退出后仍运行，则出现Zombie。
//		若父进程最后退出，其它进程接管子进程，释放，消除Zombie。
//
//	如何避免？
//		- wait/waitpid
//		- fork twice
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// 制造一个僵尸进程
void make_zombie()
{
	pid_t pid=fork();
	if(pid<0){
	}
	if(pid==0){
		exit(0);
	}
	if(pid>0){
		sleep(20); // 父进程在没有退出的情况下，子进程状态为Z（Zombie）。
				// 父进程退出，由其它进程接管子进程，并释放。
				// ps结果：[a.out] <defunct>
	}
}

// 使用wait接管一组子进程
void wait_children()
{
	int count=10;
	pid_t pidArray[count];
	int statusArray[count];
	int i=0;

	for(;i<count;i++){
		sleep(1);
		pidArray[i]=fork();
		if(pidArray[i]<0){
			perror("err when fork,i="+i);
		}else if(pidArray[i]==0){
			printf("->(child process)%d\r\n",getpid());
			sleep(1);
			exit(i);
		}else{
			int j=0;
			wait(&j);// TODO 结果是 0 128 ...
			printf("->(main process),and child status=%d\r\n",j);
		}
	}
}


int main(int c,char* v[])
{
	//make_zombie();
	wait_children();
	return 0;
}



