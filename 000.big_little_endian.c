//
//	big-endian & little-endian
//
//	big-endian
//		data:0x1234
//		data in address:[12][34] ([] means a byte)
//
//	little-endian
//		data:0x1234
//		data in address:[34][12]
//
//	一般，intel/amd均采用小端模式
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void print_size()
{
	int a=1;
	short b=1;
	char c='c';
	printf("sizeof int:%d\r\n",sizeof(a));
	printf("sizeof short:%d\r\n",sizeof(b));
	printf("sizeof char:%d\r\n",sizeof(c));
}

// 使用指针识别
void test_using_pointer()
{
	short s = 0x0102;
	char* c=(char*)&s;

	if((int)*c==0x01){
		printf("big-endian\r\n");
	}

	if((int)*c==0x02){
		printf("little-endian\r\n");
	}

	printf("%x\r\n",*c);
}

// 使用union识别
void test_using_union()
{
	union{
		short a;
		char c;
	} u;
	
	u.a=0x0102;

	printf("%d\r\n",(int)u.c);// => 2 , little-endian

}

int main(int argc,char* argv[])
{
	print_size();
	test_using_pointer();
	test_using_union();
	return 0;
}
