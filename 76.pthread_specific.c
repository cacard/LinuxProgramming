//
//	thread specific data
//	线程私有数据
//
//	键：用来关联线程私有数据，且线程通用
//		pthread_key_create
//		pthread_key_delete
//
//	键的线程安全初始化
//		pthread_once_t
//		pthread_once()

//	读写数据
//		pthread_getspecific
//		pthread_setspecific
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_once_t initflag=PTHREAD_ONCE_INIT;
pthread_key_t key;

// 初始化key
void thread_init()
{
	pthread_key_create(&key,NULL);
}

// thread1
void* thread_function1()
{
	// 创建key，仅一次
	pthread_once(&initflag,thread_init);

	// write
	pthread_setspecific(key,"value1");

	// read
	char* p=(char*)pthread_getspecific(key);
	printf("->thread1,value=%s\r\n",p);
}

void* thread_function2()
{
	pthread_once(&initflag,thread_init);

	// write
	pthread_setspecific(key,"value2");
	// read
	char* p=(char*)pthread_getspecific(key);
	printf("->thread2,value=%s\r\n",p);
}

int main()
{
	pthread_t tid1;
	pthread_t tid2;
	int r1;
	int r2;
	r1=pthread_create(&tid1,NULL,thread_function1,NULL);
	r2=pthread_create(&tid2,NULL,thread_function2,NULL);
	if(r1!=0){
		printf("error when create thread1");
		exit(1);
	}
	if(r2!=0){
		printf("error when create thread2");
		exit(1);
	}

	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);

	return 0;
}


