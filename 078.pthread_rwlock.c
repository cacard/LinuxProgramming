//
//	读写锁 pthread_rwlock_t
//
//
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_rwlock_t rwlock;

// init rwlock once
void rwlock_init()
{
	if(0 != pthread_rwlock_init(&rwlock,NULL)){
		printf("error when init\r\n");
	}
}

void* fn_read_lock()
{
	int r1=pthread_rwlock_rdlock(&rwlock);
	if(r1 !=0 ){
		printf("error when get redlock\r\n");
		return((void*)0);
	}
	// 获取读锁
	printf("->geted read-lock\r\n");
	sleep(5);

	// 释放读锁
	int r2=pthread_rwlock_unlock(&rwlock);
	if(r2 !=0 ){
		printf("error when unlock readlock\r\n");
	}else{
		printf("->release read-lock\r\n");
	}

	return ((void*)0);
}

// 线程中使用写锁
void* fn_write_lock()
{
	if(pthread_rwlock_wrlock(&rwlock)!=0){
		printf("error when get write-lock\r\n");
		return ((void*)0);
	}
	// ..进入写临界区
	printf("-> get write lock\r\n");
	sleep(3);
	if(pthread_rwlock_unlock(&rwlock)!=0){
		printf("error when unlock write-lock\r\n");
	}else{
		printf("-> release write-lock\r\n");
	}

	return ((void*)0);
}

int main(int arg_count,char* arg_values[])
{
	rwlock_init();

	// create 2 thread
	pthread_t t1,t2;
	int r1,r2;
	r1=pthread_create(&t1,NULL,fn_read_lock,NULL);
	r2=pthread_create(&t2,NULL,fn_write_lock,NULL);
	if(r1!=0){
		printf("error when creating thread1\r\n");
	}
	if(r2!=0){
		printf("error when creating thread2\r\n");
	}

	// join
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);

	// 释放锁
	pthread_rwlock_destroy(&rwlock);

	return 0;
}
