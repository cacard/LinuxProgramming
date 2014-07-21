//
//	epoll
//
//	- 完全不同于select/poll
//	- 非POSIX
//	- Linux 2.6
//	- 适合于fd数量过多的场景，因为select/poll的遍历fd影响性能
//
//	epoll_create
//	epoll_ctl
//	epoll_wait
//
//	ET/LT
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/epoll.h>

void epoll_demo()
{
	int max_fd_count=60;//监听的fd数量

	// 创建epoll上下文
	int epfd=epoll_create(max_fd_count/*近似于监听数量*/);
	if(epfd<0){
		perror("error when create epoll context");
		return;
	}

	// 打开一个fd
	int fd=STDIN_FILENO;//监听标准输入
	printf("listening fd:%d\r\n",fd);

	// 加入fd感兴趣的事件
	struct epoll_event event;
	event.data.fd=fd; //事件返回后可获得对应的fd
	event.events=EPOLLIN|EPOLLET; // 模式为ET，边缘触发
	int r=epoll_ctl(epfd,EPOLL_CTL_ADD,fd,&event);
	if(r<0){
		perror("error when epoll_ctl");
	}else{
		printf("epoll_ctl() EPOLL_CTL_ADD ok.\r\n");
	}

	// 开始监听等待
	struct epoll_event* events;
	events=malloc(sizeof(struct epoll_event)*max_fd_count);
	if(events==NULL){
		perror("error when create events array");
		return;
	}

	while(1==1){
		printf("epoll_wait\r\n");
		int return_count=epoll_wait(epfd,
			events,
			max_fd_count,//最多返回数量
			-1//阻塞等待
		);
		if(return_count<0){
			perror("error when epoll_wait");
			free(events);
		}

		printf("some events hapend,count=%d\r\n",return_count);
		int i=0;
		for(;i<return_count;i++){
			printf("->event fd=%d\r\n",events[i].data.fd);
		}
	}
}

int main(int argc,char* argv[])
{
	epoll_demo();
	return 0;
}
