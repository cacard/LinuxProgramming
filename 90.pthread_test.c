//
//

#ifdef _POSIX_THREADS
#define PTHREAD_OK 1
#endif

#include <stdio.h>
#include <pthread.h>

int main()
{
	printf("->%d",_POSIX_THREADS);
	return 0;
}
