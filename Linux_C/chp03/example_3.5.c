
#include <stdio.h>


int	Is_LeapYear(int year)
{
int ret=0;
if(year%4==0 && year%100!=0 || (year%400==0))
	ret=1;
else 
	ret=0;
	return ret;
}

void main()
{
	int is_leap;
	int year;
	scanf("%d",&year);
	is_leap=Is_LeapYear(year);
	if(is_leap)
		printf("%d is leap year.\n",year);
	else
		printf("%d is not leap year.\n",year);
}
