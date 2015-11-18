#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <netdb.h>  
#include <sys/types.h>   
#include <stdio.h>   
#include <errno.h>   
#include <sys/ioctl.h>   
#include <net/if.h>   

#include <netinet/ip.h>   
#include <netinet/in.h>   
#include <string.h>   
#include <arpa/inet.h>   
#include <netinet/tcp.h>   
#include <pthread.h>     
#include <signal.h>   

typedef struct threadpara
{
	char ip[20];
	int minport;
	int maxport;
}tp;

unsigned  short checksum(unsigned short *addr,int len)   
{
	int   nleft=len;   
	int   sum=0;   
	unsigned short *w=addr;   
	unsigned short answer=0;   
	
	while(nleft>1)   
	{   
		sum+=*w++;   
		nleft-=2;   
	}   
    
	if(nleft==1)   
	{   
		*(unsigned char*)(&answer)=*(unsigned char*)w;   
		sum+=answer;   
	}   
    
	sum=(sum>>16)+(sum & 0xffff);   
	sum+=(sum>>16);   
	answer=~sum;   
	return(answer);   
}   

// 用於標識關閉SYN掃描
int flag = 0;

void*  recv_packet(void* arg)     
{     
	struct sockaddr_in *in1;   
	char *srcaddr;   
	int loopend;   
	int size;   
	u_char readbuff[1600];   
	struct sockaddr   from;   
	int from_len;   
	struct tcphdr*  tcp;  
	struct servent* sptr; 
	tcp=(struct tcphdr *)(readbuff+20);   
	int fd = *((int *)arg);
	    
	while(1)
	{     
		if(flag == 1)
			return ;

		size = recvfrom(fd, (char *)readbuff,1600, 0,&from, &from_len);   
		if(size < 40) 
			continue;   
	//	printf("data is ok.....ack_seq:%ld,destport:%d\n",ntohl(tcp->ack_seq),ntohs(tcp->dest));
        if((ntohl(tcp->ack_seq)!=12346)||(ntohs(tcp->dest)!=10240))   
			continue;     
		if(tcp->rst&&tcp->ack)     
		{       
			printf("port:%5d | Status: closed\n",htons(tcp->source));  
			continue;   
		} 
		
		if(tcp->ack&&tcp->syn)     
		{ 
			in1=(struct sockaddr_in *)&from;;   
			srcaddr=inet_ntoa(in1->sin_addr);   
			printf("SERVER:%s\r",srcaddr);   
			if((sptr=getservbyport(tcp->source,"tcp"))!=NULL)     
			{
				printf("Port:%5d Server: %s | Status: open!!!\n",htons(tcp->source),sptr->s_name);     
			}   
			else     
				printf("Port:%5d | Status: open!!!\n",htons(tcp->source));   
			fflush(stdout);     
			continue;     
		}     
	}  
}     
int sendSyn(int sendSocket,u_long sourceIP,struct sockaddr_in *dest)     
{     
	unsigned char netPacket[sizeof(struct tcphdr)];     
	struct tcphdr* tcp;     
	u_char* pPseudoHead;     
	u_char  pseudoHead[12+sizeof(struct tcphdr)];   
	u_short  tcpHeadLen;
	
	memset(netPacket,0,sizeof(struct tcphdr));     
	
	tcpHeadLen=htons(sizeof(struct tcphdr));     
	tcp=(struct tcphdr *)netPacket;     
	tcp->source=htons(10240);     
	tcp->dest=dest->sin_port;     
	tcp->seq=htonl(12345);     
	tcp->ack_seq=0;     
	tcp->doff=5;     
	tcp->syn=1;   /*Syn的標誌*/   
	tcp->window=htons(10052);     
	tcp->check=0;     
	tcp->urg_ptr=0;     
	pPseudoHead=pseudoHead;     

	memset(pPseudoHead,0,12+sizeof(struct   tcphdr));     
	memcpy(pPseudoHead,&sourceIP,4);   
	pPseudoHead+=4;   
	
	memcpy(pPseudoHead,&(dest->sin_addr),4);   
	pPseudoHead+=5;   
	
	memset(pPseudoHead,6,1);     
	pPseudoHead++;     
	
	memcpy(pPseudoHead,&tcpHeadLen,2);     
	pPseudoHead+=2;     
	
	memcpy(pPseudoHead,tcp,sizeof(struct tcphdr));   
	tcp->check=checksum((u_short *)pseudoHead,sizeof(struct tcphdr)+12);   
	
	int temp = sendto(sendSocket,netPacket,sizeof(struct tcphdr),0,(struct sockaddr*)dest,sizeof(struct sockaddr_in));
	return  temp;     
}     
void Alarm(int sig)   
{   
	flag = 1;
}   
void synscan(char *ip,int minport,int maxport)
{  
	pthread_t tid;     
	struct ifreq if_data;   
	int fd;
	u_long addr_p;     
	char* addr;     

	struct sockaddr_in clientaddr;	
	fd=socket(AF_INET,SOCK_RAW,IPPROTO_TCP);
	if(fd<0)     
	{
		perror("error: create raw socket!!!");    
		return ;
	}
	flag = 0;
	signal(SIGALRM,Alarm);   
 
	strcpy(if_data.ifr_name,"eth0");   
	if(ioctl(fd, SIOCGIFADDR, &if_data) < 0)     
	{
		perror("error: ioctl");   
		return ;  
	}   
	memcpy((void *)&addr_p,   (void *)&if_data.ifr_addr.sa_data+2,4);   
	
	bzero(&clientaddr,sizeof(clientaddr));     
    clientaddr.sin_family=AF_INET;     
	clientaddr.sin_addr.s_addr = inet_addr(ip);
    
	printf("Now start scanning ......\n");     
	int err = 0;
	err = pthread_create(&tid,NULL,recv_packet,(void *)&fd);
	if(err < 0)     
		perror("error: create thread!!!");     
    
	int i = minport;
	for(; i<=maxport; i++)     
	{     
		clientaddr.sin_port=htons(i);     
		if(sendSyn(fd,addr_p,&clientaddr) < 0)     
		{
			perror("error: send syn!!!!"); 
		}
		alarm(3);
	}    	
	pthread_join(tid,NULL); 
}

void scan(char *ip,int minport,int maxport)
{
//	printf("test ip:%s,port:%d,port:%d\n",ip,minport,maxport);

	int i = 0;
	printf("Now start scanning ......\n");     
	for (i = minport; i <= maxport; i++)
	{
		struct sockaddr_in clientaddr;	
		struct hostent *pDest ;
		clientaddr.sin_family = AF_INET;
		clientaddr.sin_addr.s_addr = inet_addr(ip);
		clientaddr.sin_port = htons(i);
		int net = socket(AF_INET, SOCK_STREAM, 0);
		if (net < 0)
		{
			perror("error: create socket!!!!\n");
			return;
		}

		int err = connect(net, (struct sockaddr *) &clientaddr, sizeof(clientaddr));
		 
		if (err < 0) 
		{
			printf("Port:%5d | Status:closed!!!\n", i);
			fflush(stdout);
		} 
		else
		{
			struct servent* sptr; 
			if((sptr=getservbyport(htons(i),"tcp"))!=NULL)     
			{
				printf("Port:%5d | Server: %s | Status: open!!!\n",i,sptr->s_name);     
			}   
			else     
				printf("Port:%5d | Status: open!!!\n",i);  
		}
		close(net);
  }

}
void* connthread(void *threadp)
{
	struct threadpara *pThreadpara = (struct threadpara *)threadp;
	
	int i;
//	printf("minport:%d maxport:%d thread...\n",pThreadpara->minport,pThreadpara->maxport);
	for (i = pThreadpara->minport; i <= pThreadpara->maxport; i++)
	{
		struct sockaddr_in clientaddr;	
		struct hostent *pDest ;
		clientaddr.sin_family = AF_INET;
		clientaddr.sin_addr.s_addr = inet_addr(pThreadpara->ip);
		clientaddr.sin_port = htons(i);
		int net = socket(AF_INET, SOCK_STREAM, 0);
		if (net < 0)
		{
			perror("error: create socket!!!!\n");
			return;
		}
	//	printf("探測埠為:%d...............\n",i);
		int err = connect(net, (struct sockaddr *) &clientaddr, sizeof(clientaddr));
		if (err < 0) 
		{
			printf("Port:%5d | Status:closed!!!\n", i);
			fflush(stdout);
		} 
		else
		{
			struct servent* sptr; 
			if((sptr=getservbyport(htons(i),"tcp"))!=NULL)     
			{
				printf("Port:%5d | Server: %s | Status: open!!!\n",i,sptr->s_name);     
			}   
			else     
				printf("Port:%5d | Status: open!!!\n",i);  
		}
		close(net);
  }
	pthread_exit(NULL);

}
void multiscan(char *ip,int minport,int maxport,int num)
{
	if(num <= 0)
		num = 10;
	else if(num > 100)
		num = 100;

	if(maxport < minport)
	{
		printf("error: can't satify scan condition !!!\n");
		return ;
	}
	
	int count = (maxport-minport)/num;
	int i = 0;	

//	printf("count=%d,num=%d,maxport=%d,minport=%d\n",count,num,maxport,minport);
	printf("Now start scanning ......\n");     
	for(; i < num; i++)
	{
		struct threadpara threadpara;
		strcpy(threadpara.ip,ip);
		threadpara.minport = minport + count*i;
		if( i == num-1)
			threadpara.maxport = maxport;
		else
			threadpara.maxport = threadpara.minport + count;
	
	//	printf("i=%d,maxport=%d,minport=%d\n",i,threadpara.maxport,threadpara.minport);
		int temp;
		pthread_t threadid;
		temp = pthread_create(&threadid, NULL, connthread, (void *)&threadpara);     
		if(temp < 0)
			printf("create thread error !!!!! \n");
		pthread_join(threadid,NULL); 
	}	
}
void schdule(int type)
{
	printf("please input scan ip address:");
	char ip[20];
	scanf("%s",ip);
	
	printf("please input the lower limit of port:");
	int minport;
	scanf("%d",&minport);
	
	printf("please input the upper limit of port:");
	int maxport;
	scanf("%d",&maxport);
	
	int num;
	if(type == 1)
	{
		printf("please input create thread number:");
		scanf("%d",&num);
	}
	switch(type)
	{
	case 0:
		scan(ip,minport,maxport);
		break;
	case 1:
		multiscan(ip,minport,maxport,num);
		break;
	case 2:
		synscan(ip,minport,maxport);
		break;
	default:
		break;
	}
	
}
void help()
{
  printf("==================================================================\n");
  printf("version：V1.0\n");
  printf("author：my2005lb\n\n\n");
  printf("%-12s %-12s\n","Command","Fuction");
  printf("%-12s %-12s\n","scan","connect scan method");
  printf("%-12s %-12s\n","quichscan","mutlithread connect scan method");
  printf("%-12s %-12s\n","synscan","Syn scan method");
  printf("%-12s %-12s\n","hlep","Print help information");
  printf("%-12s %-12s\n","quit","Exit the program");
  printf("==================================================================\n");
}
int main(int argc, char **argv)
{
	 while(1)
	 {
	 
		 printf("please input your command:>");
		 char command[20];
	     scanf("%s",&command);
	
		 if(strcmp(command,"scan")==0)
		 {
			  schdule(0);
			  continue;
		 }
		 if(strcmp(command,"quickscan")==0)
		 {
			  schdule(1);
			  continue;
		 }
		 if(strcmp(command,"synscan")==0)
		 {
			 schdule(2);
			 continue;
		 }
		 else if(strcmp(command,"quit")==0)
		 {
			 exit(0);
			 continue;
		 }
		 else if(strcmp(command,"help") == 0)
		 {
			 help();
		 }
		 else
		 {
			 printf("Sorry,can't identify your input!!!\n");
		 }
	 }
}


