#include <stdio.h>

float fib(int n)
{
  float s;
  if(n==0||n==1) 
s=1;
  else
s=fib(n-1)+fib(n-2);
  return(s);
}
void	main()
{
  int n;
  float s;
  printf("\nPlease input n:");
  scanf("%d",&n);
  s=fib(n);
  printf("\nfib(%d)=%f",n,s);
}

