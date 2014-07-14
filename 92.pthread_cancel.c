//
//	pthread_cancel(tid)
//
//	仅仅是向被取消的线程发送取消请求，具体看线程设置。
//	
//	线程是否接受取消：pthread_setcancelate(int stat,int* oldstate)
//		- PTHREAD_CANCEL_ENABLE:默认接受请求
//		- PTHREAD_CANCEL_DISABLE:不接收请求
//
//	线程如何应对取消：pthread_setcanceltype(int type,int* oldtype)
//		- PTHREAD_CANCEL_DEFERRED:延迟取消。即执行到取消点时才取消
//		- PTHREAD_CANCEL_ASYNCHRONOUS:异步取消，即立即取消。
//
//	取消点（cancellation point）
//		- 某个函数是个取消点，比如：
//			- pthread_testcancel()
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* thread1()
{
	pthread_t pid=pthread_self();
	printf("->thread1()\r\n");
	int i=0;
	for(;i<100;i++){
		printf("1_%d,",i);
		if(i==50){
			if(pthread_cancel(pid) !=0 ){ // 自己取消自己
				printf("error when cancel.\r\n");
			}else{
				printf("thread1 canceld\r\n");
				pthread_testcancel();// 调用取消点后，才取消。
			}
		}
	}
	//exit(0);
	return((void*)0);
}

void* thread2()
{
	printf("->thread2()\r\n");
	pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,NULL);// 设置为异步取消
	int i=0;
	for(;i<100;i++){
		printf("2_%d,",i);

		if(i<10){continue;}

		if(pthread_cancel(pthread_self()) !=0 ){
			printf("error when cancel thread2\r\n");
		}else{
			printf("thread2 canceld\r\n"); // 此行不打印，线程退出。
		}
	}
	return NULL;
}

int main()
{
	// create tow threads
	pthread_t t1;
	pthread_t t2;

	if((pthread_create(&t1,NULL,thread1,NULL))!=0){
		printf("error when create thread1\r\n");
	}
	if((pthread_create(&t2,NULL,thread2,NULL))!=0){
		printf("error when create thread2\r\n");
	}

	// join
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);

	return 0;
}
