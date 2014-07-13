//
//	atexit()
//
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
	if(atexit(exit_handler_1) !=0 ){
		perror("error when register handler1");
	}
	if(atexit(exit_handler_2) !=0 ){
		perror("error when register handler2");
	}

	return 0;
}
