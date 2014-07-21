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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/epoll.h>

void epoll_demo()
{
	int max_fd_count=60;//监听的fd数量

	// 创建epoll上下文
	int epfd=epoll_create(max_fd_count);
	if(epfd<0){
		perror("error when create epoll context");
		return;
	}

	// 打开一个fd
	int fd=STDIN_FILENO;//监听标准输入

	// 加入监听
	struct epoll_event event;
	event.data.fd=fd;
	event.events=EPOLLIN|EPOLLOUT;

	// 开始监听等待
}

int main(int argc,char* argv[])
{
	epoll_demo();
	return 0;
}
