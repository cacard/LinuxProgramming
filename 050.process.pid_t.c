//
//	pid_t demo
//
//	pid_t
//		* unsign int
//
//	getpid()
//	getppid()
//	getuid()
//	geteuid()
//	getgid()
//	getegid()
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int c,char* v[])
{
	// main thread
	pid_t pid = getpid();     //process id
	pid_t ppid = getppid();   //parent process-id

	uid_t uid = getuid();     //user id
	gid_t gid = getgid();     //group id
	
	printf("\nget current process's pid/ppid/uid/gid:\n");
	printf("pid%d,ppid%d,uid%d,gid%d\r\n",pid,ppid,uid,gid);

	return 0;
}
