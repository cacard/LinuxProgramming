//
//	error 
//
//	errno 错误标号
//	perror() 打印错误标号对应的错误消息到控制台
//

#include <errno.h> // ERROR NOMBER

int main()
{
	// no error,errnum == 0
	printf("when no error,errnum is %d\r\n",errno);
	// print error
	perror("some error");

	// 打印errno代表的含义
	int i=0;
	for(;i<200;i++){
		errno=i;
		printf("errno=%d\r\n",errno);
		perror("error msg");
	}

	return 0;
}
