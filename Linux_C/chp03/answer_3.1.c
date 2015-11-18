#include <stdio.h>
void	main()
{ 
int x, max,min;
scanf("%d",&x);
max=x; min=x;
while(x>=0)
{ 
if(x>max)  
max=x;
if(x<min) 
min=x;
scanf("%d",&x); 
}
printf("\nmax=%d\nmin=%d\n",max,min); 
}
