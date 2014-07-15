//
//	stdio FILE
//
//	* 打开流
//		* FILE* fopen()
//	* 每次读写一个字符
//		* getc()/fgetc()/putc()/fputc() 
//	* 每次读写一行字符
//		* fget() 读取一个缓冲区大小以null结尾，获取读取一行以null结尾
//		* fputs() 写入一个以null结尾的字符串，null不写入。
//		* gets()/puts() 不推荐使用
//	* 直接IO
//

#include <stdio.h>
#include <stdlib.h>

// 每次读写一个字符
void once_a_char()
{
	char* file_path="30.read_only.txt";
	char* file_path_for_write="30.write.txt";
	// open FILE
	FILE* f=fopen(file_path,"r");
	if(f==NULL){
		perror("error when open FILE,==NULL");
		exit(1);
	}
	FILE* f_write=fopen(file_path_for_write,"w+");
	if(f_write==NULL){ // 写文件的情况一般不会
		perror("error when open FILE for write");
		exit(1);
	}

	// read file
	int c;
	while((c=fgetc(f))!=EOF){
		printf("->%c\r\n",c);
		// write to another file
		int r=fputc(c,f_write);
		if(r==EOF){
			perror("error when write to another file");
		}
	}
	if(ferror(f)){
		perror("error when read FILE");
		exit(1);
	}
	if(feof(f)){
		printf("end.");
	}
}

// 每次读写一行字符
void once_a_line()
{
	char* file1="30.read_only.txt";
	char* file2="30.write_line.txt";

	// open
	FILE* f1=fopen(file1,"r");
	FILE* f2=fopen(file2,"w+");
	if(f1==NULL||f2==NULL){
		perror("file is NULL");
		exit(1);
	}

	// read & write
	int buf_size=5;
	char buf[buf_size];
	char* rtn;
	while((rtn=fgets(buf,buf_size,f1))!=NULL){
		printf("->%s\r\n",buf);
		// write to another file
		int rtn2=fputs(buf,f2);
		if(rtn2==EOF){
			perror("error when write to another file");
		}
	}
}

int main()
{
	once_a_line();
	return 0;
}
