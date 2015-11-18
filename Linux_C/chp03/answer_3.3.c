#include <stdio.h>
#include <string.h>
void	main()
{
  char str[20],low[20],up[20];
  int i;
  printf("\nPlease input a string:");
  gets(str);
  printf("\nThe letter list is:\n");
  puts(str);
  i=0;
  while(str[i]!='\0')
  {
    if(str[i]>=65&&str[i]<=90)
    {
      low[i]=str[i]+32;
      up[i]=str[i];
    }
    else if(str[i]>=97&&str[i]<=122)
	{
	   low[i]=str[i];
	   up[i]=str[i]-32;
	}
    i++;
  }
  printf("\nThe result is:\n");
  puts(up);
  puts(low);
}
