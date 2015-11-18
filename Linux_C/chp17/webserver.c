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
#include <fcntl.h>  
#include <sys/types.h>   
#include <sys/stat.h>   
#include <unistd.h> 
#include <glib.h>
#include <gtk/gtk.h>

#define SERVER_PORT 80
#define MAX_BUF 8192

#define GET_COMMON   0
#define GET_CGI   1
#define HEAD   2
#define POST   3
#define BAD_REQUEST -1 

int gServerStatus = 0;
int gIsRun = 0;

FILE *pfilelog = NULL;

/* 程式執行流程為基於請求鏈的傳遞，具體流程為通過解析函數，解析本次請求鏈；
  分析本次請求鏈，調用相關模組執行，生成回應頭資訊，以及定位檔資訊
  發送回應頭資訊以及檔，更新日誌記錄
*/
typedef struct HttpRequest
{
	char method[20]; // 請求方法
	char *path; // 請求路徑及資源名，若為CGI則為請求的可執行程式路徑
	char *content; //　請求內容，面向POST和GET CGI請求
	int contentlength; //　請求內容的長度
	int			contenttype;	/* 迴響的內容類別型: */
	int			rangeflag;     /* 以下用於中斷點續傳，分別表示中斷點起始點，結束點以及總長度*/
	long		rangestart;
	long		rangeend;
	long		rangetotal;	
	char	    prefix[20];
	int  responsecode; //回應碼
}HR;

/*
  解析請求，　順次解析各行
*/
FILE* isexistfile(char *filename)
{
	FILE *fp = NULL;
	fp = fopen(filename,"r");
	return fp;
}

int getrequest(char *requestbuf,struct HttpRequest *prequest)
{
	char protocol[20];	
	char path[200];
	int i = 0;
	if(sscanf(requestbuf, "%s %s %s", prequest->method, path, protocol)!=3)
		return BAD_REQUEST;
	if(strcmp(prequest->method,"GET") == 0)
	{
		if(strchr(path, '?') == NULL)
		{
			// 先判斷是否最後一個字元為/,如果為/則，掛加index.htm
			if(path[strlen(path)-1] == '/')
				strcat(path,"index.htm");
			//在之前添加./web 這是預設目錄
			sprintf(prequest->path,"./web%s",path);
			// 求尾碼資訊，若沒有，則置為*
			if(sscanf(path, "%s.%s", path, prequest->prefix)!=2)
				strcpy(prequest->prefix,"*");
			
			printf("GET path:%s\nprefix:%s\n",prequest->path,prequest->prefix);
			return GET_COMMON;
		}
		else
		{
			prequest->content = (char *)malloc(strlen(prequest->path));
			printf("run ?  \n");
			sscanf(prequest->path,"%s?%s",prequest->path, prequest->content);
			printf("run ?  %s|%s \n",prequest->path, prequest->content);
			return GET_CGI;
		}	
	}		
	else if(strcmp(prequest->method,"POST") == 0)
	{
		return POST;
	}
	else if(strcmp(prequest->method,"HEAD") == 0)
	{
		return HEAD;
	}
	else if(strcmp(prequest->method,"TRACR") == 0)
	{
		return TRACR;
	}
	return -1;
}
char* getcontenttype(char *type)
{
	// 返回內容type
	char ContentType[][27] ={
			"jpeg", "image/jpeg",
			"png", "image/png",
			"mpg", "video/mpeg",
			"asf", "video/x-ms-asf",
			"avi", "video/x-msvideo",
			"bmp", "image/bmp",
			"doc", "application/msword",
			"exe", "application/octet-stream",//14, 15
			"rar", "application/octet-stream",
			"zip", "application/zip",
			"jpg", "image/jpeg",
			"gif", "image/gif",
			"txt", "text/plain",
			"c", "text/plain",
			"cpp", "text/plain",
			"cxx", "text/plain",
			"h", "text/plain",
			"ico", "image/x-icon",
			"css", "text/css",
			"htm", "text/html",
			"html", "text/html"
			"*", "application/octet-stream"
	};	
	int nType = sizeof(ContentType)/27;
	int i;
	for(i=0; i<nType; i+=2)
	{
		if(strcmp(ContentType[i], type) == 0)
			return ContentType[i+1];
	}
    return "application/octet-stream";
}
char* getcurrenttime()
{
/*	char timebuf[30];
	struct tm *p;
	long ltime;
	time(&ltime);
	p=localtime(&ltime);
	strftime(timebuf,25,"%a %d %b %Y %H:%M:%S",p);
	/*
	time_t now;
	struct tm *timenow;
	char localvalue[30];
	time(&now);
	timenow = localtime(&now);
	sprintf(localvalue,"%s",asctime(&now));
//	localvalue[strlen(localvalue)-1] = '\0';
	printf("localtime :%s\n",localvalue);
	*/
	time_t timep;
	char localvalue[30];
	time (&timep);

	sprintf(localvalue,"%s",asctime(gmtime(&timep)));
	printf("localtime :%s",localvalue);
	return localvalue;
}
// 構建回應碼，發送回應碼資訊
void responsecode(int s,int code,struct HttpRequest *prequest)
{

	char buffer[2048];
	char contenttype[200];
	char content[1023];
	
	prequest->responsecode = code;
	// 構建回應報文頭
	switch(code)
	{
	case 200:
		sprintf(buffer,
			"HTTP/1.1 200 OK\r\n"
			"Server: LiuServer/1.0\r\n"
			"Date: %s\r\n"
			"Content-Type: %s\r\n"
			"Accept-Ranges: bytes\r\n"			
			"Content-Length: %d\r\n"
			"Connection: close\r\n"
			//"\r\n",date,contenttype,prequest->rangetotal);
			"\r\n",getcurrenttime(),getcontenttype(prequest->prefix),prequest->rangetotal);
		break;
	case 404:
		strcpy(content,"<html><head><title>Object Not Found</title></head><body><h1>Object Not Found</h1>File Not Found.</body></html>");
		sprintf(buffer,
			"HTTP/1.1 404 Object Not Found\r\n"
			"Server: LiuServer/1.0\r\n"
			"Date: %s\r\n"			
			"Content-Type: %s\r\n"
			"Content-Length: %d\r\n"
			"Connection: close\r\n"
			"\r\n"
			"%s", getcurrenttime(),getcontenttype(prequest->prefix),strlen(content), content);
		break;
	case 505:
		break;
	default:
		break;
	}
	sendsegment(s,buffer,strlen(buffer));
}
void processgetcommon(int s,struct HttpRequest *prequest)
{
	//　先判斷檔是否存在
	FILE *fp = isexistfile(prequest->path);
	printf("%s\n",prequest->path);
	struct stat finfo; 
	if(fp == NULL)
	{
		responsecode(s,404,prequest);
	}
	else
	{		
		if(prequest->rangeflag == 0)
		{			
			stat(prequest->path,&finfo);
			prequest->rangetotal = finfo.st_size;
		}
		responsecode(s,200,prequest);
		transferfile(s,fp,prequest->rangeflag,prequest->rangestart,prequest->rangetotal);
		fclose(fp);
	}
}
void processgetcgi(int s,struct HttpRequest *prequest)
{
	system("hello");
	
}
void processpost(int s,struct HttpRequest *prequest)
{

}
void processhead(int s,struct HttpRequest *prequest)
{

}
// 參數的含義為
int transferfile(int s,FILE *fp,int type,int rangstart,int totallength)
{
	if(type == 1)
	{
		//　為1　則表示當前從指定的位置傳送檔
		fseek(fp,rangstart,0);		
	}
	int sendnum = 0;
	int segment = 1024;
	while(!feof(fp)&&sendnum < totallength)
	{
		char buf[segment];
		memset(buf,0,1024);
		int i = 0;
		while(!feof(fp) && i < segment && sendnum+i < totallength)
		{		
			buf[i++] = fgetc(fp);					
		}
		if(sendsegment(s,buf,i) == 0)
			return 0;
		sendnum += i;
	}
	return 1;
}
int sendsegment(int s, char *buffer,int length)
{
	if(length <= 0)
		return 0;
	printf("%s\n",buffer);
	int result = send(s,buffer,length,0);
	if(result < 0)
		return 0;
	return 1;
}

// 日誌檔採用XML格式存儲
FILE* openlogfile(FILE *fp)
{
	char filename[200];
	sprintf(filename,"./log/%s.xml",getcurrenttime());
	fp = fopen(filename,"ab+");
	if(fp == NULL)
	{
		printf("can't open this file[%s]\n",filename);
		return NULL;
	}
	fputs("<?xml version=\"1.0\" encoding=\"GB2312\"?>",fp);
	fputs("<Log>",fp);
	fflush(fp);
	return fp;
}
void closelogfile(FILE *fp)
{
	if(fp == NULL)
		return;
	fputs("</Log>",fp);
	fclose(fp);
}

void insertlognode(FILE *fp,struct HttpRequest *prequest)
{
	if(fp == NULL)
		return;
	fputs("<record>",fp);
	fputs("<method>",fp);
	fputs(prequest->method,fp);
	fputs("</method>",fp);
	fputs("<path>",fp);
	fputs(prequest->path,fp);
	fputs("</path>",fp);
	char reponsecode[100];
	sprintf(reponsecode,"<reponsecode>%d</reponsecode>",prequest->responsecode);
	fputs(reponsecode,fp);
	fputs("</record>",fp);
	fflush(fp);
}
void* processthread(void *para)
{
	int clientsocket;
	char buffer[1024];
	int iDataNum =0;
	int recvnum=0;
	clientsocket = *((int *)para);
	printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<BEGIN [%d]>>>>>>>>>>>>>>>>>>>>>>>\n",clientsocket);
	struct HttpRequest httprequest;
	httprequest.content = NULL;
	httprequest.path = NULL;
	httprequest.path = (char *)malloc(1024);
	httprequest.rangeflag = 0;
	httprequest.rangestart = 0;

	while(1)
	{
		iDataNum = recv(clientsocket,buffer+recvnum,sizeof(buffer)-recvnum-1,0);
		if(iDataNum <= 0)
		{
			close(clientsocket);
			pthread_exit(NULL);
			return 0;
		}
		recvnum += iDataNum;
		buffer[recvnum]='\0';
		if(strstr(buffer,"\r\n\r\n")!=NULL || strstr(buffer,"\n\n")!=NULL)
			break;
	}
	printf("request: %s\n",buffer);
	
	//解析請求資訊並處理請求資訊
	switch(getrequest(buffer,&httprequest))
	{
	case GET_COMMON:
		processgetcommon(clientsocket,&httprequest);
		break;
	case GET_CGI:
		processgetcgi(clientsocket,&httprequest);
		break;
	case POST:
		processpost(clientsocket,&httprequest);
		break;
	case HEAD:
		processhead(clientsocket,&httprequest);
		break;
	default:
		break;
	}			
	insertlognode(pfilelog,&httprequest);
	if(httprequest.path != NULL)
		free(httprequest.path);
	if(httprequest.content != NULL)
		free(httprequest.content);
	close(clientsocket);
	printf("<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<END [%d]>>>>>>>>>>>>>>>>>>>>>>>\n",clientsocket);
	pthread_exit(NULL);	
}
void* server_process(void *p)
{
	int serverSocket;
	struct sockaddr_in server_addr;
	struct sockaddr_in clientAddr;
	int addr_len = sizeof(clientAddr);	

	if((serverSocket = socket(AF_INET,SOCK_STREAM,0)) < 0)
	{
		perror( "error: create server socket!!!");
		exit(1);
	}

	bzero(&server_addr,sizeof(server_addr));
	server_addr.sin_family =AF_INET;
	server_addr.sin_port = htons(SERVER_PORT);
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	if(bind(serverSocket,(struct sockaddr *)&server_addr,sizeof(server_addr)) < 0)
	{
		perror("error: bind address !!!!");
		exit(1);
	}

	if(listen(serverSocket,5)<0)
	{
		perror("error: listen !!!!");
		exit(1);
	}
	gIsRun = 1;	
	printf("LiuServer is running.....\n");

	while(gIsRun)
	{		
		int clientsocket;
		clientsocket = accept(serverSocket,(struct sockaddr *)&clientAddr,(socklen_t*)&addr_len);
		if(clientsocket < 0)
		{
			perror("error: accept client socket !!!");
			continue;
		}
		if(gServerStatus == 0)
		{
			close(clientsocket);
		}
		else if(gServerStatus == 1)
		{
			pthread_t threadid;
			int temp;
			temp = pthread_create(&threadid, NULL, processthread, (void *)&clientsocket);   
			/*if(threadid !=0) 
			{                   
				 pthread_join(threadid,NULL);
			}*/
		}
	}	
	close(serverSocket);
}
 
void run_button( GtkWidget *widget,
               gpointer   data )
{
   // g_print ("run was pressed\n");
	if(gIsRun == 0)
	{
		pthread_t threadid;
		int temp;
		temp = pthread_create(&threadid, NULL, server_process, NULL);  
		gServerStatus = 1;
	}
	else
	{
		if(gServerStatus == 0)
			gServerStatus = 1;
		else
		{
			printf("is runnning.....\n ");
		}
	}
	gtk_label_set_text( (GtkLabel*)data,"Server Status: run...."); 
}
void pause_button( GtkWidget *widget,
               gpointer   data )
{
	if(gIsRun == 1)
	{
		if(gServerStatus == 1)
		{
			gServerStatus = 0;
		}
		else
		{
			printf("is pause\n");
		}
		gtk_label_set_text( (GtkLabel*)data,"Server Status: pause");	
	}
	else
	{
		printf("need run....\n");
	}
	
}

gint close_application( GtkWidget *widget,
                        GdkEvent  *event,
                        gpointer   data )
{
/*	if(gIsRun == 1)
	{
		gIsRun = 0;		
		while(!gIsRun)
		{
			sleep(1);
			printf("waitting for end................\n");
		}
	}
*/
	closelogfile(pfilelog);
	gtk_main_quit ();
	return FALSE;
}

int main( int   argc,
          char *argv[] )
{
    GtkWidget *window = NULL;
    GtkWidget *box1;
    GtkWidget *box2;
    GtkWidget *button;
	GtkWidget *label;
    GtkWidget *separator;

	
  
    gtk_init (&argc, &argv);    
      
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
  
    g_signal_connect (G_OBJECT (window), "delete_event",
		      G_CALLBACK (close_application),
                      NULL);

    gtk_window_set_title (GTK_WINDOW (window), "LiuServer 1.0");
    gtk_container_set_border_width (GTK_CONTAINER (window), 20);

    box1 = gtk_vbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (window), box1);
    gtk_widget_show (box1);

    box2 = gtk_vbox_new (FALSE, 10);
    gtk_container_set_border_width (GTK_CONTAINER (box2), 10);
    gtk_box_pack_start (GTK_BOX (box1), box2, TRUE, TRUE, 0);
    gtk_widget_show (box2);

	
	label = gtk_label_new ("Server Status: stop");

    button = gtk_button_new_with_label ("Run");
	g_signal_connect (G_OBJECT (button), "clicked",
		      G_CALLBACK (run_button), G_OBJECT(label));

    gtk_box_pack_start (GTK_BOX (box2), button, TRUE, TRUE, 0);
    gtk_widget_show (button);

    
    button = gtk_button_new_with_label ("Pause");
	g_signal_connect (G_OBJECT (button), "clicked",
		      G_CALLBACK (pause_button), G_OBJECT(label));
    gtk_box_pack_start (GTK_BOX (box2), button, TRUE, TRUE, 0);
    gtk_widget_show (button);

    button = gtk_button_new_with_label ("Stop");
    gtk_box_pack_start (GTK_BOX (box2), button, TRUE, TRUE, 0);
	g_signal_connect_swapped (G_OBJECT (button), "clicked",
                              G_CALLBACK (close_application),
                              window);
    gtk_widget_show (button);

    separator = gtk_hseparator_new ();
    gtk_box_pack_start (GTK_BOX (box1), separator, FALSE, TRUE, 0);
    gtk_widget_show (separator);

    box2 = gtk_vbox_new (FALSE, 10);
    gtk_container_set_border_width (GTK_CONTAINER (box2), 10);
    gtk_box_pack_start (GTK_BOX (box1), box2, FALSE, TRUE, 0);
    gtk_widget_show (box2);

    
    
    gtk_box_pack_start (GTK_BOX (box2), label, TRUE, TRUE, 0);
    GTK_WIDGET_SET_FLAGS (button, GTK_CAN_DEFAULT);
    gtk_widget_grab_default (button);
    gtk_widget_show (label);
    gtk_widget_show (window);
     
    gtk_main ();

    return 0;
}
