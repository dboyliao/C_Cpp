
#include <stdio.h>

void	main()
{
char *max_ptr,*min_ptr;
char str[3][20];
int i;
for(i=0;i<3;i++)
gets(str[i]);
if(strcmp(str[0],str[1])>0) 
{
	max_ptr = str[0]; min_ptr = str[1];
}
else
{
	max_ptr = str[1]; min_ptr = str[0];
}
if(strcmp(str[2],max_ptr)>0)
	max_ptr = str[2];
if(strcmp(str[2],min_ptr)<0)
	min_ptr = str[2];
printf("\nThe largest string is:%s",max_ptr);
printf("\nThe smallest string is:%s",min_ptr);	
}
