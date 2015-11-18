#include<unistd.h>
#include<stdio.h>
int main()
{
	char buf[80];
	if(getcwd(buf,80)!=NULL)
		printf("The current directory is %s\n",buf);
	else 
		printf("failed!\n");
	return 1;
}
