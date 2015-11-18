#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netdb.h>
#include <errno.h>

int main()
{
	int clientsocket; 
    struct sockaddr_in serveraddress,clientaddress;     
	
    clientsocket = socket(AF_INET, SOCK_DGRAM, 0); 
    serveraddress.sin_family = AF_INET; 
    serveraddress.sin_port = htons(5050); 
    serveraddress.sin_addr.s_addr = htonl(INADDR_ANY); 
	
	int opt = 1;
	if(setsockopt(clientsocket, SOL_SOCKET, SO_REUSEADDR,&opt, sizeof(opt)) < 0)
	{ 
		perror("setsockopt:SO_REUSEADDR");
		return 0;
	}

    if(bind(clientsocket,(struct sockaddr*)&serveraddress,sizeof(struct sockaddr)) != 0) 
    { 
        perror("bind");
		return 0; 
    } 
	char buf[200]; 
    while (1) 
    { 
		memset(buf,0,200);
		int size = 0; 
		size = recvfrom(clientsocket,buf,200,0, (struct sockaddr *)&clientaddress,sizeof(clientaddress));
		buf[size] = '\0';
		printf("IP:%s msg:%s\n",inet_ntoa(clientaddress.sin_addr),buf); 
		
		if(strcmp(buf,"quit") == 0)
		{
			printf("system quit!!!!\n");
			close(clientsocket);
			return 0;
		}
    }
	return 0; 
}