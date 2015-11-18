#include<stdio.h>
int main()
{
	FILE *fp;
	fp=fopen("temp.txt","a+");
	if(fp==NULL)
	return 0;
	else 
	printf("open file succeeded!\n");
	fclose(fp);
	return 1;
}
