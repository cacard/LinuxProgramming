//
//	进程退出方式
//
//	正常退出
//		- return(int status);
//		- exit(int status); ISO C
//		- _Exit(int status); ISO C 不清理资源
//		- _exit(int status); Posix 不清理资源
//
//	异常退出
//		- 收到导致退出的信号，例如
//			- SIGABRT
//			- SIGALRM
//			- SIGINIT
//

#include <stdioh>
#include <stdlib.h>
#include <unistd.h>


int main(int c,char* v[])
{

	// 正常终止
	return 0;
}
