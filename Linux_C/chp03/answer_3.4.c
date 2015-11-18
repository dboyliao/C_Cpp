#include <stdio.h>
void	main()
{
	int	i,j,temp,array[4][4];
printf("Input 4*4 data:\n"); 
for(i=0;i<4;i++) 
for(j=0;j<4;j++) 
scanf("%d",&array[i][j]);
	for(i=0;i<4;i++)
		for(j=0;j<4;j++)
			if(i!=j)
			{
				temp=array[i][j]; array[i][j]= array[j][i]; array[j][i]=temp;
			}
for(i=0;i<4;i++) 
{
	printf("\n");
for(j=0;j<4;j++) 
printf("%d\t",&array[i][j]);
	}
}

