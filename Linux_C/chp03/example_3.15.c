
#include <stdio.h>

void	Sort(int array[],int n)
{
int i,j,temp;
for(j=1;j<n;j++)
for(i=0;i<=n-j;i++)
	if(array[i]> array[i+1])
{
temp= array[i]; array[i]= array[i+1]; array[i+1]=temp;
}
}
void   main()
{
int i;
int arr[10];
int *i_ptr;
for(i=0;i<10;i++)
scanf("%d",&arr[i]);
Sort(arr,10);
for(i_ptr=arr; i_ptr<(arr+10); i_ptr++)
printf("%d ",*i_ptr);	
    printf("\n");
}
