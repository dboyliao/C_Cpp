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

#define SERVER_PORT 5555

main()
{
	int serverSocket;
	struct sockaddr_in server_addr;
	struct sockaddr_in clientAddr;
	int addr_len = sizeof(clientAddr);
	int client;
	char buffer[1024];
	int iDataNum ;

	if((serverSocket = socket(AF_INET,SOCK_STREAM,0)) < 0)
	{
		perror("socket");
		exit(1);
	}

	bzero(&server_addr,sizeof(server_addr));
	server_addr.sin_family =AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if(bind(serverSocket,(struct sockaddr *)&server_addr,sizeof(server_addr)) < 0)
	{
		perror("connect");
		exit(1);
	}

	if(listen(serverSocket,5)<0)
	{
		perror("listen");
		exit(1);
	}

	while(1)
	{		
		client = accept(serverSocket,(struct sockaddr *)&clientAddr,(socklen_t*)&addr_len);
		if(client < 0)
		{
			perror("accept");
			continue;
		}
		iDataNum = recv(client,buffer,1024,0);
		if(iDataNum < 0)
		{
			perror("Recv");
			continue;
		}
		printf("\nRecv client data.......\n");
		printf("IP is %s\n",inet_ntoa(clientAddr.sin_addr));
		printf("Port is %d\n",htons(clientAddr.sin_port));
		printf("Recv Data is %s\n",buffer);
		send(client,buffer,sizeof(buffer),0);
	}					
}
