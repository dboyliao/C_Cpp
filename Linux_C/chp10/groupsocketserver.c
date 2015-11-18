#include<stdio.h> 
#include<sys/types.h> 
#include<sys/socket.h> 
#include<netinet/in.h> 
#include<arpa/inet.h> 

#define MAXBUF 256 

int port = 5000; 
char *multicast_addr= "224.0.1.1"; 

int main(int argc,char *argv[]) 
{ 
	
	int   serversocket,n; 
	struct   sockaddr_in   serveraddr,clientaddr; 
	int   cli_len=sizeof(clientaddr); 
	struct   ip_mreq   mreq; 
	char   buf[MAXBUF]; 
	
	bzero(&serveraddr,sizeof(serveraddr)); 
	serveraddr.sin_family=AF_INET; 
	serveraddr.sin_addr.s_addr=htonl(INADDR_ANY); 
	serveraddr.sin_port=htons(port); 
	
	if((serversocket=socket(AF_INET,SOCK_DGRAM,0)) <0) 
	{ 
		perror("error: create socket!!!"); 
		return   0; 
	} 
	
	if(bind(serversocket,(struct sockaddr*)&serveraddr,sizeof(serveraddr)) <0) 
	{ 
		perror("error: bind error!!!"); 
		return   0; 
	} 
	
	mreq.imr_multiaddr.s_addr=inet_addr(multicast_addr); 
	mreq.imr_interface.s_addr=htonl(INADDR_ANY); 
	
	if(setsockopt(serversocket,IPPROTO_IP,IP_ADD_MEMBERSHIP,&mreq,sizeof(mreq)) <0) 
	{ 
		perror("error: setsockopt"); 
		return 0; 
	} 
	
	while(1) 
	{ 
		if((n=recvfrom(serversocket,buf,MAXBUF,0,(struct sockaddr*)&clientaddr,&cli_len)) <0) 
		{ 
			perror("error: recvfrom"); 
			return 0; 
		} 
		else 
		{ 
			buf[n]='\0'; 
			printf("receive msg from %s : %s\n ",inet_ntoa(clientaddr.sin_addr),buf); 
		} 
		if(sendto(serversocket,buf,strlen(buf),0,(struct  sockaddr*)&serveraddr,sizeof(serveraddr)) <0) 
		{ 
			perror( "sendto "); 
			return  0; 
		} 
		else 
		{ 
			fprintf(stdout, "send  to  group  %s  :  %s\n ",multicast_addr,buf); 
		}	 
	} 
	
	return 1; 
} 
