
#include <stdio.h>

void  main()
{
int	array[10]={12,32,27,8,22,54,19,40,34,22};
int i, max,index;
max = array[0];
index=0;
for(i=0;i<10;i++)
{
if(array[i]>max)
{
	max= array[i];
	index=i;
}
}
printf("max=%d,index=%d\n",max, index);
}
