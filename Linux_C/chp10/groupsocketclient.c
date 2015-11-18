#include<stdio.h> 
#include<sys/types.h> 
#include<sys/socket.h> 
#include<netinet/in.h> 
#include<string.h> 
#include<arpa/inet.h> 

#define   MAXBUF   256 
int   port=5000; 
char  *multicast_addr= "224.0.1.1"; 

int main(int argc, char *argv[]) 
{ 
	int serversocket; 
	struct sockaddr_in   serveradd; 
	char buf[MAXBUF]; 
	
	bzero(&serveradd,sizeof(serveradd)); 
	serveradd.sin_family=AF_INET; 
	serveradd.sin_addr.s_addr=inet_addr(multicast_addr); 
	serveradd.sin_port=htons(port); 
	
	serversocket=socket(AF_INET,SOCK_DGRAM,0); 
	if(serversocket <0) 
	{ 
		perror("error: create socket !!!!"); 
		return 0; 
	} 
	
	while(1) 
	{ 
		printf("please input your word:>");
		fgets(buf,MAXBUF,stdin); 
		if(sendto(serversocket,buf,strlen(buf),0,(struct sockaddr*)&serveradd,sizeof(serveradd)) <0) 
		{ 
			perror("error: sendto"); 
			return   0; 
		} 
		else 
		{ 
			printf("send to group %s : %s\n ",multicast_addr,buf); 
		} 
	} 	
	return 1; 
}