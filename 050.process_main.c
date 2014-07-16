//
//	main()
//
//	arg_c/arg_v

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int arg_count,char* arg_values[])
{
	if(arg_count==0){
		printf("only one default parameter\r\n");
		printf("->arg_values[0]=%s\r\n",arg_values[0]);
	}else{
		int i=0;
		for(;i<arg_count;i++){
			printf("%d parameters:\r\n",arg_count);
			printf("->%s\r\n",arg_values[i]);
		}
	}

	exit(0);
}
