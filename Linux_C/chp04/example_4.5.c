#include<stdio.h>
int main()
{
	int flag;
	char s[]="temp.txt";
	flag=remove(s);
	if(flag==0)
		printf("delete file successfully!\n");
	else
    		printf("failed!\n");
	return 1;
}
