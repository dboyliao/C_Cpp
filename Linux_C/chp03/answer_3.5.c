#include <stdio.h>

int mon(int year,int month,int day);
int leap_year(int year);

void main()
{
	int day,month,year,sum;
	
	printf("\nplease input year,month,day\n");
	scanf("%d,%d,%d",&year,&month,&day);
	sum=mon(year,month,day);
	printf("It is the %dth day.",sum);
}
int mon(int year,int month,int day) 
{
int sum,leap;
switch(month)/*先計算某月以前月份的總天數*/
{
	case 1:
			sum=0;
			break;
	case 2:
			sum=31;break;
	case 3:
			sum=59;break;
	case 4:
			sum=90;break;
	case 5:
			sum=120;break;
	case 6:
			sum=151;break;
	case 7:
			sum=181;break;
  case 8:
			sum=212;break;
  case 9:
			sum=243;break;
  case 10:
			sum=273;break;
  case 11:
			sum=304;break;
  case 12:
			sum=334;break;
  default:
			printf("data error");break;
}
	sum=sum+day; /*再加上某天的天數*/
	leap=leap_year(year);
	if(leap==1&&month>2)/*如果是閏年且月份大於2,總天數應該加一天*/
		sum++;
	return sum;
}
int leap_year(int year)
{
	int leap;
	if(year%400==0||(year%4==0&&year%100!=0))
		leap=1;
	else
		leap=0;
  return leap;
}

