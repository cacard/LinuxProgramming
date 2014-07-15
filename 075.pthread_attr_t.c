//
//	线程属性 pthread_attr_t
//
//	* 对用户不透明
//	* 可通过一些函数设置一些属性：
//		- pthread_detach
//		- pthread_cancel
//		- pthread_getconcurrency
//
//

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void test_pthread_attr_t()
{
	// init
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	// set attr

	// using attr create a thread

	// destroy attr
	pthread_attr_destroy(&attr);
}

int main()
{
	test_pthread_attr_t();
	return 0;
}
