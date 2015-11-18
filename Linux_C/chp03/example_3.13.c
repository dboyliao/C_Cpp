
#include <stdio.h>

void  main()
{
int	array_two[4][6]=
{{20,1,32,3,4,45},{4,45,6,87,8,9},{8,29,10,11,2,3},{2,19,0,-11,22,53}};
int i,j,max,index1,index2;
max= array_two[0][0];
index1=0;
index2=0;
for(i=0;i<4;i++)
for(j=0;j<6;j++)
	if(array_two[i][j]>max)
	{
		max = array_two[i][j];
		index1=i;
		index2=j;
	}
printf("max=%d, index1=%d,index2=%d\n",max, index1,index2);
}
