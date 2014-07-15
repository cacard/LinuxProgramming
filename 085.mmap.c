//
//	mmap
//	内存直接映射文件
//
//

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

void test_mmap()
{
	char* path="./txt/mmap.txt";
	int map_len=10;

	// open file
	int fd = open(path,O_RDWR);
	if(fd<0){
		perror("error when open file");
		exit(1);
	}

	// 映射
	char* addr = (char*)mmap(0,map_len,PROT_WRITE,MAP_SHARED,fd,0);
	if(addr==NULL){
		perror("error when mmap");
	}

	// change map
	addr[0]='@';

	// flush
	int r0=msync(addr,map_len,MS_SYNC);
	if(r0!=0){
		perror("error when msync");
	}

	// 解除映射
	int r1=munmap(addr,map_len);
	if(r1!=0){
		perror("error when munmap");
	}
}

int main()
{
	test_mmap();
	return 0;
}
