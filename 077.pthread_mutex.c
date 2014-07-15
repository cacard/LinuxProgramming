//
//	mutex
//
//	静态创建
//		PTHREAD_MUTEX_INITIALIZER 
//	动态创建
//		pthread_mutext_init()
//		...lock()/...trylock()
//		...unlock
//		...destroy
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int count=0;

void test_critical_region()
{
	// 创建
	pthread_mutex_t mutex;
	// 动态创建
	int r1=pthread_mutex_init(&mutex,NULL);
	if(r1 !=0 ){
		perror("error when init mutex");
	}
	// 加锁
	int r2=pthread_mutex_lock(&mutex);
	if(r2 !=0 ){
		printf("error when lock\r\n");
	}
	// 进入临界区
	count++;
	// 解锁
	int r3=pthread_mutex_unlock(&mutex);
	if(r3 !=0){
		printf("error when unlock\r\n");
	}
	// 动态创建的 pthread_mutex_t 需要释放资源
	pthread_mutex_destroy(&mutex);
}


int main(int arg_count,char* args[])
{
	test_critical_region();
	printf("->count=%d\r\n",count);
	return 0;
}
