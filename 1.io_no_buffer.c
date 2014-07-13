//
//	io no-buffer
//
//	需要手动设置BufferSize
//	open()/read()/write()/lseek()	
//
//

#include <stdio.h> // stdio
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h> // common function

static char* path="1.io_no_buffer.txt";

void write_file()
{
	printf("\r\n---write_file()---\r\n");

	// open file
	int fd=open(path,O_RDWR|O_CREAT);
	char data[]={'a','b','c'};
	int len=sizeof(data)/sizeof(data[0]);
	size_t writed_count=write(fd,data,len);
	if(writed_count<0){
		perror("error when write");
		exit(1);
	}
	printf("write success.len=%d\r\n",len);

	// close file
	close(fd);
}

void read_file()
{
	printf("\r\n---read_file()---\r\n");

	// open file
	int fd = open(path,O_RDONLY);
	if(fd<0)
	{
		perror("error when open file");
		exit(1);
	}

	// read file
	int buffer_size=1024;
	char bf[buffer_size];
	int count=0;
	while((count=read(fd,bf,buffer_size))>0){
		printf("->%s\r\n",bf);
	}
	if(count<0){
		perror("error when read file");
		exit(1);
	}
	if(count==0){
		printf("read end.\r\n");
	}

	close(fd);
}

int main()
{
	write_file();
	read_file();
	return 0;
}
