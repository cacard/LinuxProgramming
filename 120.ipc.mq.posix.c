//
//	message queue (Posix)
//
//	link with -lrt
//
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <mqueue.h> // lrt
#include <sys/stat.h>
#include <pthread.h> // lpthread
#include <string.h>

char* MQ_NAME="/mq_demo"; // just stat with slash
int MSG_MAX_SIZE=9999;

// 创建MQ
mqd_t create_mq()
{
	mqd_t mqd=mq_open(MQ_NAME,O_RDWR|O_CREAT,S_IRUSR|S_IWUSR,NULL);
	if(mqd<0){
		perror("error when create mq");
	}
	return mqd;
}

// 打印MQ属性
void print_mq(mqd_t mqd)
{
	struct mq_attr attr;
	if(mq_getattr(mqd,&attr) !=0 ){
		perror("error when get mq attr");
		return;
	}

	printf("mq_attr:\r\n");
	printf("mq_flags:%ld\r\n",attr.mq_flags);
	printf("mq_maxmsg:%ld\r\n",attr.mq_maxmsg);
	printf("mq_msgsize:%ld\r\n",attr.mq_msgsize);
	printf("mq_curmsgs:%ld\r\n",attr.mq_curmsgs);

}

// 销毁关闭
void destroy_mq(mqd_t mqd)
{
	if(mq_unlink(mqd)!=0){
		perror("error when close mq");
	}
}

// 消息生产者线程
void* thread_productor(void* arg)
{
	// open mq
	mqd_t mqd=mq_open(MQ_NAME,O_WRONLY,NULL,NULL); // Write Only
	if(mqd==-1){
		perror("error when open mq in productor");
		return ((void*)0);
	}

	// send msg
	int i=0;
	int count=10;
	for(;i<count;i++){
		char* msg="hello";
		if((mq_send(mqd,msg,strlen(msg),0))!=0){
			perror("error when send msg");
		}else{
			printf("productor send a msg over,i=%d\r\n",i);
			sleep(1);
		}
	}
	//close
	if(mq_close(mqd)!=0){
		perror("error when close mq in productor");
	}

	//

	return NULL;
}

// 消息消费者线程
void* thread_consumer(void* arg)
{
	// open mq
	mqd_t mqd=mq_open(MQ_NAME,O_RDONLY,NULL,NULL);
	if(mqd==-1){
		perror("error when open mq in consumer");
		return NULL;
	}

	// receive msg
	while(1==1){
		char buf[9999];
		int p;
		printf("try receive msg\r\n");
		ssize_t s=mq_receive(mqd,buf,9999,&p); // may block
		if(s==-1){
			perror("error when receive msg");
			continue;
		}else{
			printf("receive a msg,size=%d,prio=%d,msg=%s\r\n",s,p,buf);
		}
	}

	// close
	if(mq_close(mqd) !=0 ){
		perror("error when close mq in consumer");
	}

	return NULL;
}

// 启动生产者和消费者
void start_productor_consumer()
{
	pthread_t tid1,tid2;
	int r1,r2;

	r1=pthread_create(&tid1,NULL,thread_productor,NULL);
	r2=pthread_create(&tid2,NULL,thread_consumer,NULL);

	if(r1!=0){perror("error when create thread_productor");}
	if(r2!=0){perror("error when create thread_consumer");}

	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
}

int main(int c,char* v[])
{
	// create mq
	mqd_t mqd=create_mq();
	if(mqd<0){
		printf("error when create mq\r\n");
		exit(0);
	}

	// print default attr
	print_mq(mqd);

	// start
	start_productor_consumer();

	// unlink mq and destroy
	destroy_mq(mqd);

	return 0;
}
