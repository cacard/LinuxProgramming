//
//	错误处理 
//
//	errno:错误标号
//	perror(msg):打印错误标号对应的错误消息到控制台
//	strerror(errno):标号转化成语义

#include <errno.h> // ERROR NOMBER

int main()
{
	// no error,errnum == 0
	printf("when no error,errnum is %d\r\n",errno);
	// print error
	perror("some error");

	char* err_means=strerror(1);
	printf("error_emans=%s\r\n",err_means);

	// 打印errno代表的含义
	int i=0;
	for(;i<200;i++){
		errno=i;
		printf("errno=%d\r\n",errno);
		perror("error msg");
	}

	return 0;
}
