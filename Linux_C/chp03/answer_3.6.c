#include <stdio.h>
#define N 50
void main()
{
int n,i,j,k,a[N],b[N]; 
	for (k=0;k<N;k++) b[k]=a[k]=0; 
	/*詢問要輸出多少層,不超過50*/ 
printf("Input n=");
scanf("%d",&n); 
	b[1]=1; 
	for (i=1;i<=n;i++)/*依次輸出每一層*/
	{ 
		/*數組b中為上一層的數，下面語句利用數組b生成當前層的數組a*/ 
		a[0]=1;
		for (j=1;j<i;j++) 
			a[j]=b[j-1]+b[j]; 
		/*下面語句輸出左邊的空格：第i層左邊空n-i個格，沒格寬度為3*/ 
		for (j=0;j<n-i;j++) 
			printf("%3c",32); 
		/*下面語句輸出本層的數字，每個寬度3，空白3*/ 
		for (j=0;j<i;j++) 
			printf("%3d%3c",a[j],32); 
		/*下面的語句輸出換行*/ 
		printf("\n"); 
		/*下面的語句把當前數組a複製到b中*/ 
		for (k=0;k<N;k++) 
			b[k]=a[k]; 
	} 
	printf("\n");
}
