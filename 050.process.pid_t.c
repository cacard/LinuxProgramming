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
	pid_t pid=getpid();
	pid_t ppid=getppid();

	uid_t uid=getuid();
	gid_t gid=getgid();

	printf("pid%d,ppid%d,uid%d,gid%d\r\n",pid,ppid,uid,gid);

	return 0;
}
