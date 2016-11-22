//
//	atexit()
//	- 进程退出时的清理函数
//	- 对应的，线程有pthread_cleanup_xxx函数
//	- 可登记多个
//	- 调用次序与登记次序相反
//	- 重复登记，重复调用
//

#include <stdlib.h>
#include <stdio.h>

void exit_handler_1()
{
	printf("exit handler 1\r\n");
}
void exit_handler_2()
{
	printf("exit handler 2\r\n");
}

int main()
{
	// register handler1
	if(atexit(exit_handler_1) !=0 ){
		perror("error when register handler1");
	}

	// register handler2
	if(atexit(exit_handler_2) !=0 ){
		perror("error when register handler2");
	}

	printf("I will exit...\n");

	return 0;
}
