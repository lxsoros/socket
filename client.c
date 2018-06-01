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
	
	if ( connect(sock,(struct sockaddr*)&name,sizeof(name))!=0)
	{
		perror("connect");
		exit(EXIT_FAILURE);
	}
	const char* msg="hello jesse";
	write(sock,msg,strlen(msg));
	char buffer[64]={0};
	read(sock,buffer,64);
	puts(buffer);


	return 0;
}


