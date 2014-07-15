//
//	select
//
//	经常用在socket场景中
//	对于 regular file则一直ready-write/ready-read的。
//
//	fd_set
//		FD_ZERO()
//		FD_SET()
//		FD_CLR()
//		FD_ISSET()
//
//
//	pselect
//	与select类似，timeout更精确，可添加信号屏蔽
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
	// 添加并置位
	FD_SET(1,&set);
	FD_SET(2,&set);
	FD_SET(3,&set);
	// 删除
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

void test_select()
{

}

int main(int argc,char* argv[])
{
	test_fd_set();
	return 0;
}
