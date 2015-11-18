
#include <stdio.h>

long Recursion (int n);
void  main()
{
int num;
long factorial;
scanf("%d",&num);
factorial = Recursion(num);
printf("%d!=%ld\n",num, factorial);
}
long  Recursion (int n)
{
if(n>1)
return n* Recursion (n-1); /*遞迴調用*/
else if(n==1 || n==0)
return 1;
else
  {
printf("Invalid argument!\n");
exit(-1);            /*正常退出*/
   }
}
