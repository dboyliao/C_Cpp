#include <stdio.h>
void	main()
{ 
	int	m,n,number1,number2,temp;
	printf("Please enter 2 numbers m,n:");
scanf("%d,%d",&m,&n);
number1=m; number2=n;
if(m>n)
{
	temp = m; m=n; n=temp;
}

while(n!=0)
{
	temp=m%n; m=n; n=temp;
}
printf("The GCD of  %d,%d is:%d", number1, number2,m);
printf("The LCM of  %d,%d is:%d", number1, number2, number1* number2/m);

}

