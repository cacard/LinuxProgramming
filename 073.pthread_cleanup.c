//
//	pthread_cleanup_push
//
//
//	pthread_cleanup_pop
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void clean()
{
	printf("->clean1\r\n");
}
void clean_()
{
	printf("->clean2\r\n");
}

void* thread_function()
{	
	pthread_t tid=pthread_self();
	printf("->enter thread,tid=%u\r\n",(unsigned int)tid);
	
	// register clean function
	pthread_cleanup_push(clean,NULL);
	pthread_cleanup_push(clean_2,NULL);

	printf("->exiting thread\r\n");
	return ((void*)0);
}

void test()
{
	pthread_t tid;
	int r;
	r=pthread_create(&tid,NULL,thread_function,NULL);
	if(r!=0){
		printf("error when create thread\r\n");
	}else{
		printf("create thread success.tid=%u\r\n",(unsigned int)tid);
	}

	// join
	pthread_join(tid,NULL);
}

int main()
{
	test();
	return 0;
}

