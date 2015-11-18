
#include <stdio.h>

void  func(int x)
{  
int a=0;
static int b=0;
a++;   b++;
printf("%d: a=%d, b=%d\n", x, a, b);
}
void  main( )
{  
int  i;
for (i=1; i<=3; i++)
    func(i);
}
