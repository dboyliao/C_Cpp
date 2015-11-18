#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<sys/socket.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include <arpa/inet.h>
#include<netdb.h>

#define PORT 7773
#define MAXDATASIZE 256

int main(int argc,char *argv[])
{
    int socket_fd;
    struct sockaddr_in my_addr,user_addr;
    char buf[MAXDATASIZE];
    int so_broadcast=1;
    socklen_t size;
    char my_ip[12];
	
    my_addr.sin_family=AF_INET;
    my_addr.sin_port=htons(PORT);
    my_addr.sin_addr.s_addr=inet_addr("255.255.255.255");
    bzero(&(my_addr.sin_zero),8);
    
    user_addr.sin_family=AF_INET;
    user_addr.sin_port=htons(PORT);
    user_addr.sin_addr.s_addr=htonl(INADDR_ANY);
    bzero(&(user_addr.sin_zero),8);
    if((socket_fd=(socket(AF_INET,SOCK_DGRAM,0)))==-1) {
        perror("socket");
        exit(1);
    }
    setsockopt(socket_fd,SOL_SOCKET,SO_BROADCAST,&so_broadcast,sizeof(so_broadcast));
    if((bind(socket_fd,(struct sockaddr *)&user_addr,
		sizeof(struct sockaddr)))==-1) {
        perror("bind");
        exit(1);
    }
    strcpy(buf,"Hello,I'm on line!");
    sendto(socket_fd,buf,strlen(buf),0,(struct sockaddr *)&my_addr,sizeof(my_addr));
    size=sizeof(user_addr);
    recvfrom(socket_fd,buf,MAXDATASIZE,0,(struct sockaddr *)&user_addr,&size);
    strcpy(my_ip,inet_ntoa(user_addr.sin_addr));
    printf("my_ip:%s\n",inet_ntoa(user_addr.sin_addr));
    while(1) {
        bzero(buf, sizeof(buf));          
        size=sizeof(user_addr);
        recvfrom(socket_fd,buf,MAXDATASIZE,0,(struct sockaddr *)&user_addr,&size);
        printf("%s:%s\n",inet_ntoa(user_addr.sin_addr),buf);
        bzero(buf, sizeof(buf));
        if(strcmp(buf,"I'm off line,bye!")==0)
            strcpy(buf,"ok,I know,bye!");
        else {
            strcpy(buf,"send,Hello,I get you!");
			sleep(1);
        }    
        if((sendto(socket_fd,buf,strlen(buf),0,
			(struct sockaddr *)&user_addr,sizeof(user_addr)))==-1)
            perror("sendto");
    }
    return 0;
}

