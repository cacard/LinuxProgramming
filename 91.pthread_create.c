//
//	pthread
//
//	gcc x.c -lpthread
//
//	pthread_t
//		- pthread_self()
//
//	pthread_create()
//
//
//	pthread_join(tid)
//


#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

// 当前线程id
void test_pthread_t()
{
	pthread_t tid=pthread_self();
	printf("->main thread's pthread_t=%u (0x%x)\r\n",(unsigned int)tid,(unsigned int)tid);
}

// 创建线程

void* new_thread_function()
{
	pthread_t tid=pthread_self();
	printf("->runing in new thread,tid=%u\r\n",(unsigned int)tid);
	return ((void*)0);
}
void test_pthread_create()
{
	pthread_t tid;
	int rtn;
	rtn=pthread_create(
		&tid,
		NULL,// pthread_attr_t 线程属性
		new_thread_function,//线程调用函数
		NULL//调用函数时的参数
		);
	if(rtn!=0){
		perror("error when create thread");
		printf("error when create thread,rtn=%d\r\n",rtn);
	}else{
		printf("create thread success,tid=%u\r\n",(unsigned int)tid);
	}

	// join线程
	pthread_join(tid,NULL);
}


int main()
{
	pid_t pid = getpid();
	printf("->main process's pid=%d\r\n",pid);

	test_pthread_t();
	test_pthread_create();

	return 0;
}
