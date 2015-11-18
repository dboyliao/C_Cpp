#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

main()
{	
	struct sockaddr_in serverAddr;
	int clientSocket;
	char sendbuf[200];
	char recvbuf[200];
	if((clientSocket=socket(AF_INET,SOCK_STREAM,0)) < 0)
	{
		perror( "socket error" );
		return -1; 		
	}
	
	serverAddr.sin_family=AF_INET;
	serverAddr.sin_port=htons(5555);
	serverAddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	if(connect(clientSocket,( struct sockaddr * )&serverAddr,sizeof(serverAddr)) < 0)
	{
		perror("connect");
		exit(1);
	}	
	printf("connect with destination host.....\n");
	while(1)
	{
		printf("Input your World:>");
		scanf("%s",sendbuf);
		printf("\n");
		
		if(strcmp(sendbuf,"quit") == 0)
			break;

		send(clientSocket,sendbuf,sizeof(sendbuf),0);
		recv(clientSocket,recvbuf,200,0);
		printf("recv data of my world is: %s\n",recvbuf);
	}
	close(clientSocket);
	return 0;
}
