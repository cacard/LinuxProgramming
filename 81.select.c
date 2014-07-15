//
//	select
//
//	fd_set
//		FD_ZERO()
//		FD_SET()
//		FD_CLR()
//		FD_ISSET()
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/select.h>

void test_fd_set()
{
	printf("->FD_SETSIZE=%d\r\n",FD_SETSIZE);

	fd_set set;
	// 清零
	FD_ZERO(&set);
	// 添加值
	FD_SET(1,&set);
	FD_SET(2,&set);
	FD_SET(3,&set);
	// 清除某一位
	FD_CLR(3,&set);
	
	int i=1;
	for(;i<=5;i++){
		int j;
		if((j=FD_ISSET(i,&set))){
			printf("fd%d is set,j=%d\r\n",i,j);
		}else{
			printf("fd%d is not set,j=%d\r\n",i,j);
		}
	}
}

int main(int argc,char* argv[])
{
	test_fd_set();
	return 0;
}
