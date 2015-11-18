#include<stdio.h>
int addcount(int value,int count)
{
  int i = 1;
  for(; i <= count; i++)
  {
    value += i;
  }
  return value;
}
int subcount(int value,int count)
{
  int i = 1;
  for(; i <= count; i++)
  {
    value -= i;
  }
  return value;
}
int main(int argc,char *argv[] )
{
  int value = 0;
  if(argc == 2)
     value = atoi(argv[1]);  
  printf("value is :%d\n",value);
  value = subcount(value,10);
  printf("value is :%d\n",value);
¡¡return 0;
}
