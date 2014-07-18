//
//	stat 文件信息
//	
//	stat() / fstat() / lstat()
//

#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>

void print_stat(const struct stat* _s)
{
	printf("stat:\r\n");
	printf("dev_t:%d\r\n",_s->st_dev); 
	printf("ino_t,st_ino:%d\r\n",_s->st_ino);
	printf("mode_t,st_mode:%d\r\n",_s->st_mode);
	printf("uid_t,st_uid:%d\r\n",_s->st_uid);
}

int main()
{
	char* path="0.hello.c";

	// stat(char* file,struct stat* buf)
	struct stat fileStat;
	if(stat(path,&fileStat)<0){
		perror("error when stat()");
		exit(1);
	}
	print_stat(&fileStat);

	// fstat(int fd,struct stat* buf)
	
	return 0;
}
