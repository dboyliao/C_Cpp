#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{ 
	struct ip_mreq multiaddress; 	
	int serveraddress_len;	
	int client_socket;
	struct sockaddr_in serveraddress;
	
	/*bzero(&serveraddress, sizeof(serveraddress));*/
	memset(&serveraddress, 0, sizeof(serveraddress));
	serveraddress.sin_family = AF_INET;
	serveraddress.sin_addr.s_addr = htonl(INADDR_ANY);
	serveraddress.sin_port = htons(5555);
	if((client_socket = socket(PF_INET, SOCK_DGRAM, 0)) < 0) 
	{ 
		perror("socket");
		return 0;
	}
	
	int opt = 1;
	if(setsockopt(client_socket, SOL_SOCKET, SO_REUSEADDR,&opt, sizeof(opt)) < 0)
	{ 
		perror("setsockopt:SO_REUSEADDR");
		return 0;
	}
	if(bind(client_socket, (struct sockaddr *)&serveraddress, sizeof(serveraddress)) < 0)
	{
		perror("bind"); 
		return 0;
    }

	// 在同一个主机上进行广播设置套接口
	multiaddress.imr_multiaddr.s_addr = inet_addr("224.0.0.1"); 
	multiaddress.imr_interface.s_addr = htonl(INADDR_ANY);
	
	// 加入广播组
	if (setsockopt(client_socket,IPPROTO_IP,IP_ADD_MEMBERSHIP,&multiaddress, sizeof(multiaddress)) < 0)
	{   
		perror("IP_ADD_MEMBERSHIP");
		return 0;
    } 

	while(1) 
	{    
		char buf[200];
		serveraddress_len = sizeof(serveraddress); 
		if(recvfrom(client_socket, buf, 200, 0,	(struct sockaddr *)&serveraddress, &serveraddress_len) < 0) 
		{ 
			perror("recvfrom");   
		}  
		printf("msg from server: %s\n", buf);

		if(strcmp(buf,"quit") == 0)
		{			
			if(setsockopt(client_socket, IPPROTO_IP, IP_DROP_MEMBERSHIP,&multiaddress, sizeof(multiaddress)) < 0) 
			{ 
				perror("setsockopt:IP_DROP_MEMBERSHIP"); 
			}   
			close(client_socket); 
			return 0;
		}
	} 	
}
