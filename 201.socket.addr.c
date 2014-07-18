//
//	ip addr/socket addr
//
//	ip address
//		- in_addr_t
//		- in_addr
//		
//		- inet_addr() . string->in_addr_t
//		- inet_ntoa() -> in_addr->string
//
//	socket address
//		- sockaddr_in
//		- sockaddr
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>

// ip address related
void test_ipaddr()
{
	// string -> in_addr
	char* ipstring="127.0.0.1";
	struct in_addr addr;
	addr.s_addr=inet_addr(ipstring); 

	// in_addr -> string
	char* ipstring2;
	ipstring2=(char*)inet_ntoa(addr);
	if(ipstring2!=NULL){
		printf("->%s\r\n",ipstring2);
	}
}

// socket address related
void test_socketaddr()
{
	// ipv4
	struct in_addr addr;
	addr.s_addr=inet_addr("127.0.0.1");

	// ipv4 socket addr
	struct sockaddr_in mySocketAddr;
	mySocketAddr.sin_family=AF_INET;
	mySocketAddr.sin_port=80;
	mySocketAddr.sin_addr=addr;

	// ipv4 common socket addr
	// convert using pointer.do not using type.
	struct sockaddr* commonSockAddr=(struct sockaddr*)&mySocketAddr;

}


int main(int argc,char* argv[])
{
	test_ipaddr();
	test_socketaddr();
	return 0;
}
