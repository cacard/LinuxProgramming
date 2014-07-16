//
//	孤儿进程 
//		orphan process
//		无害
//		父进程退出后，子进程依然运行。此种状态即时孤儿进程。
//		孤儿进程立即由init收养并作为其父进程，所以孤儿进程不会变成僵尸。
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void make()
{
	pid_t pid;
	pid=fork();

	if(pid==0){
		printf("child pid is %d\r\n",getpid());
		sleep(30);
		exit(0);
	}
	exit(0);
	// 由init立即领养
	// pid ppid 
	// 8272 1  ./a.out
}

int main(int c,char* v[])
{
	make();
	return 0;
}
