#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>

void main()
{
	int flag;
	FILE *fp;	
	char pathname[]="/root/temp";
	flag=mkdir(pathname,O_RDWR);//以讀寫方式創建一個目錄
	if(flag==0)
		printf("craete succeed!\n");
	else 
		printf("craete succeed!\n");
	if(!flag)
	{
		fp=fopen("/root/temp/temp.txt","w+");
	}
	flag=rmdir(pathname);
	printf("flag=%d\n",flag);
	if(flag==0)
		printf("delete succeed!\n");
	else 
		printf("delete failed!\n");
	
}
