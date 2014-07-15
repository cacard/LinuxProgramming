//
//	signal handler function
//
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void signal_handler(int sig)
{
	printf("catched a signal:%d\r\n",sig);
}

int main()
{
	// register signal to handler
	signal(SIGALRM,signal_handler);

	// generate a signal
	int n=alarm(5);
	
	// pause the process and wait a signal
	if(pause()==-1){
		perror("error when pause");
	}

	printf("end of main\r\n");
}
