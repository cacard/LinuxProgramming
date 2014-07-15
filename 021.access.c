//
//	access()
//	权限测试,文件是否存在

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>

int main(int argc,char * argv[])
{
	if(argc!=2){
		printf("need only one parameter");
		return 1;
	}

	// file exist?
	if(access(argv[1],F_OK)<0){
		printf("file not exist\r\n");
		return 1;
	}

	// can read?
	int r=access(argv[1],R_OK);
	if(r<0){
		printf("can not read\r\n");
	}else{
		printf("can read\r\n");
	}

	return 0;
}
