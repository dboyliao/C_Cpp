#include <stdio.h>
#include <stdlib.h>
#include <pcap.h> 
#include <errno.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

typedef unsigned char UCHAR;
typedef unsigned short USHORT;

void pcap_handle(u_char *user,const struct pcap_pkthdr *header, const u_char *pkt_data);

typedef struct{    //定義乙太幀的頭部資料類型
	UCHAR DestMac[6];
	UCHAR SrcMac[6];
	UCHAR Etype[2];   
}ETHHEADER;
typedef struct  {   //IP頭部的資料類型
        UCHAR  header_len:4;
        UCHAR  version:4;   
        UCHAR  tos:8;            // type of service
        USHORT  total_len:16;      // length of the packet
        USHORT  ident:16;          // unique identifier
        USHORT  flags:16;          
        UCHAR  ttl:8;            
        UCHAR  proto:8;          // protocol ( IP , TCP, UDP etc)
        USHORT  checksum:16;       
        UCHAR  sourceIP[4];
        UCHAR  destIP[4];
		        
}IPHEADER;
typedef struct {//定義埠資料類型用於解析TCP和UDP中的源埠和目的埠
	USHORT srcPort;
	USHORT decPort;
}PORT;
char *Proto[] = {"Reserved", "ICMP", "IGMP", "GGP", "IP", "ST", "TCP",
 "UCL", "EGP", "IGP", "BBN-RCC-MON", "NVP-II", "PUP",
 "ARGUS", "EMCON", "XNET", "CHAOS", "UDP", "MUX", 
 "DCN-MEAS", "HMP", "PRM", "XNS-IDP", "TRUNK-1", 
"TRUNK-2", "LEAF-1", "LEAF-2", "RDP", "IRTP", "ISO-TP4", "NETBLT","MFE-NSP", 
"MERIT-INP", "SEP", "3PC", "IDPR", "XTP", "DDP", "IDPR-CMTP", "TP++", "IL", "SIP", 
"SDRP", "SIP-SR", "SIP-FRAG", "IDRP", "RSVP", "GRE", "MHRP", "BNA", "SIPP-ESP",  
"SIPP-AH", "I-NLSP", "SWIPE", "NHRP", "unassigned", "unassigned","unassigned", 
"unassigned", "unassigned", "unassigned","any host internal protocol", "CFTP", "any local network", "SAT-EXPAK", "KRYPTOLAN", "RVD", "IPPC", "any distributed file system",  
"SAT-MON", "VISA", "IPCV", "CPNX", "CPHB", "WSN", "PVP", "BR-SAT-MON", "SUN-ND", 
"WB-MON", "WB-EXPAK", "ISO-IP",  "VMTP", "SECURE-VMTP", "VINES", "TTP", 
"NSFNET-IGP", "DGP", "TCF", "IGRP", "OSPFIGP", "Sprite-RPC", "LARP", "MTP", "AX.25", 
"IPIP", "MICP", "SCC-SP", "ETHERIP", "ENCAP", "any private encryption scheme", "GMTP"};

int npacketnum;
int main(void)
{
        char *device = "eth0";
        char errbuf[PCAP_ERRBUF_SIZE];
        pcap_t *phandle;
        bpf_u_int32 ipaddress, ipmask;
        struct bpf_program fcode;
        int datalink;
        if ((device = pcap_lookupdev(errbuf)) == NULL)
		{
			perror(errbuf);
			return 0;
		}
        else
		{
			printf("device: %s\n", device);
		}

        phandle = pcap_open_live(device, 200, 0, 500, errbuf);
        if (phandle == NULL)
        {
			perror(errbuf);
			return 0;
		}

        if (pcap_lookupnet(device, &ipaddress, &ipmask, errbuf) == -1)
		{
			perror(errbuf);
			return 0;
		}
        else 
		{                                         
            char net[INET_ADDRSTRLEN], mask[INET_ADDRSTRLEN];
            if (inet_ntop(AF_INET, &ipaddress, net, sizeof(net)) == NULL)
			{
				perror("inet_ntop");
			}
            else if (inet_ntop(AF_INET, &ipmask, mask, sizeof(net)) == NULL)
            {
				perror("inet_ntop");
			}
            printf("IP Address: %s, Network Mask: %s\n", net, mask);
        }

		int bflag = 1;
		while(bflag)
		{
			printf("Input Packet Filter:>");
			char filterString[1024];
			scanf("%s",filterString);
			if (pcap_compile(phandle, &fcode, filterString, 0, ipmask) == -1) {
                fprintf(stderr, "pcap_compile: %s,please input again......\n", pcap_geterr(phandle));                
			}
			else
				bflag = 0;
		}

        if (pcap_setfilter(phandle, &fcode) == -1) 
		{
                fprintf(stderr, "pcap_setfilter: %s\n", pcap_geterr(phandle));
				return 0;
        }

        if ((datalink = pcap_datalink(phandle)) == -1)
		{
                fprintf(stderr, "pcap_datalink: %s\n", pcap_geterr(phandle));
                return 0;
        }
        printf("datalink = %d\n", datalink);
       // capture_packet(datalink, phandle, fcode);
		npacketnum = 0;
		pcap_loop(phandle, 0, pcap_handle, NULL);// 
        return 1;
}
//void dispatcher_handler(u_char *user,const struct pcap_pkthdr *header, const u_char *pkt_data)
void pcap_handle(u_char *user,const struct pcap_pkthdr *header, const u_char *pkt_data)
{

	ETHHEADER *eth_header = (ETHHEADER *)pkt_data;//解析資料包的乙太幀頭部
	printf("================Begin Analysis [%d] Packet ====================\n",npacketnum++);
	printf("packet length:%ld \n",header->len);
	if (header->len >= 14)// 解析資料包的IP頭部
	{
	
		IPHEADER *ip_header=(IPHEADER *)(pkt_data+14);

		// 解析出協議類型
		char strtype[100];
		if (ip_header->proto > 99)
			strcpy(strtype ,"IP/UNKNOWN");
	    else
			strcpy(strtype, Proto[ip_header->proto]);

		printf("Source MAC:%02X-%02X-%02X-%02X-%02X-%02X ==>", eth_header->SrcMac[0],
			eth_header->SrcMac[1], eth_header->SrcMac[2], eth_header->SrcMac[3],
			eth_header->SrcMac[4], eth_header->SrcMac[5]);// 提取源MAC地址
        printf("Dest MAC:%02X-%02X-%02X-%02X-%02X-%02X \n", eth_header->DestMac[0],
			eth_header->DestMac[1], eth_header->DestMac[2], eth_header->DestMac[3],
			eth_header->DestMac[4], eth_header->DestMac[5]);//提取目的MAC位址
        // 提取源IP地址
		printf("Source IP:%d.%d.%d.%d==>",ip_header->sourceIP[0] ,ip_header->sourceIP[1],ip_header->sourceIP[2],
			ip_header->sourceIP[3]);
		// 提取目的IP位址
		printf("Dest IP:%d.%d.%d.%d\n",ip_header->destIP[0] ,ip_header->destIP[1],ip_header->destIP[2],
			ip_header->destIP[3]);
		
		//顯示協定類型
		printf("Protocol:%s\n",strtype);
		if((strcmp("TCP",strtype)==0)
			||(strcmp("UDP",strtype)==0))
		{
			//如果協議是UDP,TCP解析埠號
			PORT *port=(PORT *)(pkt_data+14+20);
			printf("Source Port:%d==>",ntohs(port->srcPort));
			printf("Dest Port:%d\n",ntohs(port->decPort ));
		}

		//顯示資料幀的內容
		u_char *p = pkt_data;
		int i;
		for( i= 0; i < (int)header->len; i++)
		{
			printf("%02X ", *p++);			
			if( (i + 1) % 25== 0)
				printf("\r\n");
		}
		printf("\n================END Analysis Packet ====================\n");
	}
}
