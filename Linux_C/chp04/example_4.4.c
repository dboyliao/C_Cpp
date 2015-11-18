#include<unistd.h>
#include<stdio.h>
int main ()
{
	int fd,size;
	char c;
	FILE *stream=fopen("temp.txt","a+");//a+表示以附加的方式打開可讀寫的文件
	c=fgetc(stream);
	printf("%c\n",c);
	c=fputc(c,stream);
	printf("%c\n",c);
	return 1;	
}
