#include<stdio.h>
int main()
{
	int flag;
	char old[]="temp.txt";
	char ne[]="new.txt";
	flag=rename(old,ne);
	if(flag==0)	
		printf("succeed!\n");
	else
		printf("failed!\n");	
	return 1;
}
