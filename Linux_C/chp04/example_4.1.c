#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
int main ()
{
	int fd,size;
	char s[]="This is a linux programe!\n",buffer[80];
	fd =open("temp.txt",O_WRONLY|O_CREAT);	
	write(fd,s,sizeof(s));
	close(fd);
	fd=open("temp.txt",O_RDONLY);	
	size=read(fd,buffer,sizeof(buffer));
	close(fd);
	printf("%s",buffer);
	return 1;
	
}