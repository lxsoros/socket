/*************************************************************************
    > File Name: local.c
    > Author: jesse
    > Mail: 2572399525@qq.com 
    > Created Time: Fri 01 Jun 2018 03:44:15 PM UTC
 ************************************************************************/

#include<stdio.h>
#include <stddef.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <unistd.h>

int main( int argc, char*const * args )
{
	const char* filename=args[1];
	struct sockaddr_un name;
	struct sockaddr_un clientname;
	int sock;
	size_t size;
	/* create the socket*/
	sock=socket(PF_LOCAL, SOCK_STREAM,0);
	if(sock<0)
	{
		perror("socket creation");
		exit(EXIT_FAILURE);
	}
	/* bind a name to the socket */
	name.sun_family=AF_LOCAL;
	strcpy(name.sun_path,filename);
	name.sun_path[sizeof(name.sun_path)-1]='\0';
	size=SUN_LEN(&name);
	if (bind(sock,(struct sockaddr*)&name,size)<0)
	{
		perror("bind");
		exit(EXIT_FAILURE);

	}
	
	char buffer[1024]={0};
	socklen_t len=1024;
	getsockname(sock,(struct sockaddr*)buffer,&len);
	puts(buffer+2);
	listen(sock,1);
	while(1)
	{
	int client=	accept(sock,(struct sockaddr*)&clientname,&len);
	write(client,"hello world",64);
	}


	return 0;
}


