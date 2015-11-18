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
	int peerSocket;
	struct sockaddr_in self_addr;
	struct sockaddr_in peer_Addr;
	int peer_len = sizeof(peer_Addr);

	char recvbuf[1024];
	char sendbuf[1024];

	if((peerSocket = socket(AF_INET,SOCK_DGRAM,0)) < 0)
	{
		perror("socket");
		exit(1);
	}

	bzero(&self_addr,sizeof(self_addr));
	self_addr.sin_family =AF_INET;
	self_addr.sin_port = htons(SERVER_PORT);
	self_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
	if(bind(peerSocket,(struct sockaddr *)&self_addr,sizeof(self_addr)) < 0)
	{
		perror("connect");
		exit(1);
	}

	while(1)
	{			
		printf("Input your World:>");
		scanf("%s",sendbuf);
		printf("\n");
		sendto(peerSocket,sendbuf,1024,0,(struct sockaddr *)&self_addr,sizeof(self_addr));
		recvfrom(peerSocket,recvbuf,1024,0,(struct sockaddr *)&peer_Addr,(socklen_t*)&peer_len);
		printf("recv from %s\n",recvbuf);
	}					
