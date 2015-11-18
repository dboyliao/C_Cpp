#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <errno.h>

#define BUFFSIZE 
#define PORT 5050

int main()
{
	int serversocket; 
    struct sockaddr_in serveraddress,clientaddress; 
    
    int so_broadcast = 1; 
    socklen_t size; 
	
    if((serversocket=(socket(AF_INET,SOCK_DGRAM,0))) < 0) 
	{
		perror("socket");
		return 0;
	}
	
    if(setsockopt(serversocket,SOL_SOCKET,SO_BROADCAST,&so_broadcast,sizeof(so_broadcast)) < 0) 
	{
		perror("setsockopt");
		return 0;
	} 
	
    serveraddress.sin_family=AF_INET; 
    serveraddress.sin_port=htons(INADDR_ANY); 
    serveraddress.sin_addr.s_addr= htonl(INADDR_BROADCAST); 
	
    if((bind(serversocket,(struct sockaddr *)&serveraddress, sizeof(struct sockaddr))) < 0) 
	{
		perror("bind");
		return 0;
	}
	
    clientaddress.sin_family=AF_INET; 
    clientaddress.sin_port=htons(PORT); 
    clientaddress.sin_addr.s_addr= htonl(INADDR_BROADCAST); 
 
	
    while (1) 
    { 
		char buf[200]; 
		printf("please input your word:>");
		scanf("%s",buf);
        if((sendto(serversocket,buf,strlen(buf),0,(struct sockaddr *)&clientaddress,sizeof(clientaddress))) < 0) 
		{
			perror("sendto error");
			return 0;
		}
        else 
            printf("send msg %s\n",buf); 
	}
	return 0; 
} 
