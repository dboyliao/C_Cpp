
#include <stdio.h>

#define SQUARE(x)	x*x


void  main()
{
int	s=0;
s = SQUARE(9); //右側展開，本句即為s = 9*9
printf("s=%d\n",s);
}
