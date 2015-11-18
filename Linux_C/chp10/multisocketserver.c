#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{    
	int server_socket;  
	struct sockaddr_in address;  

    server_socket = socket(AF_INET, SOCK_DGRAM, 0);  
	if (server_socket < 0) 
	{      
		perror("socket"); 
		return 0; 
	}   

	memset(&address, 0, sizeof(address));   
	address.sin_family = AF_INET;  
	address.sin_addr.s_addr = inet_addr("224.0.0.1"); 
	address.sin_port = htons(5555);  

	while(1)
	{ 
		char buf[200];
		printf("input your word:>");
		scanf("%s",buf);
		if(sendto(server_socket, buf,sizeof(buf), 0,(struct sockaddr *)&address, sizeof(address)) < 0) 
		{  
			perror("sendto");  
			return ;
		}   
	}  
}
