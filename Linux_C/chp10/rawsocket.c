#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <linux/if_ether.h>
#include <linux/in.h>

#define BUFFER_MAX 2048

int main(int argc, char *argv[])
{
        
	int rawsock;	     
	char buffer[BUFFER_MAX];
	char *ethhead;
	char *iphead;
	char *tcphead;
	char *udphead;
	char *icmphead;
	char *pHead;
	
	if((rawsock = socket(PF_PACKET,SOCK_RAW,htons(ETH_P_IP))) < 0)
    {
        printf("error: create raw socket!!!\n");
        exit(0);
    }
	long framecount = 0;
	while(1) 
	{
		int readnum = recvfrom(rawsock, buffer,2048,0, NULL, NULL);
        
		if(readnum < 42) 
		{
			printf("error: Header is incomplete!!!\n");
			continue;
		}
		
        ethhead = (char *)buffer;
        pHead = ethhead;
        int ethernetmask = 0XFF;
		framecount++;
		printf("------------------Analysis   Packet [%d]---------------------\n",framecount);
		printf("MAC:");
		int i = 6;
		for(; i <=11; i++)
		{
			printf("%.2X:",pHead[i]&ethernetmask);
		}
		printf("---->");
		for(i = 0; i <=5; i++)
		{
			printf("%.2X:",pHead[i]&ethernetmask);
		}
		printf("\n");
		
		iphead = ethhead + 14;  
		pHead = iphead + 12;
        
		printf("IP:");
		for(i = 0; i <=3; i++)
		{
			printf("%d",pHead[i]&ethernetmask);
			if(i != 3)
				printf(".");
		}
		printf("---->");
		for(i = 4; i <=7; i++)
		{
			printf("%d",pHead[i]&ethernetmask);
			if(i != 7)
				printf(".");
		}
		printf("\n");

		int prototype = (iphead + 9)[0];
		pHead = iphead + 20;

		printf("Protocol: ");
		switch(prototype)
		{
		case IPPROTO_ICMP:
			printf("ICMP\n");
			break;
		case IPPROTO_IGMP: 
			printf("IGMP\n");
			break;
		case IPPROTO_IPIP: 
			printf("IP\n");
			break;
		case IPPROTO_TCP :
			printf("TCP | source port: %u | ",(pHead[0]<<8)&0XFF00 | pHead[1]&0XFF);
			printf("dest port: %u\n", (pHead[2]<<8)&0XFF00 | pHead[3]&0XFF);
			break;
		case IPPROTO_UDP : 
			printf("UDP | source port: %u | ",(pHead[0]<<8)&0XFF00 | pHead[1]&0XFF);
			printf("dest port: %u\n", (pHead[2]<<8)&0XFF00 | pHead[3]&0XFF);
			break;
		case IPPROTO_RAW : 
			printf("RAW\n");
			break;
		default:
			printf("Unkown\n");
        }
		printf("-------------------------end-----------------------\n");
	}
}
