//
//	exec*
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void test_execl()
{
	char* path="/bin/vi";
	int r=execl(path,"vi",(void*)0/*or NULL*/);
	if(r==-1){
		perror("error when execl()");
	}
}

int main(int argc,char* argv[])
{
	test_execl();
	return 0;
}


