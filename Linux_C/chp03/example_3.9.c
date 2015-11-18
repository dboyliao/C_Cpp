
#include <stdio.h>

float	pi=3.14f;
float	Area(float radius)
{
float s;
s=pi*radius*radius;
return	s;
}
void main( )
{
float	radius,area=0;
scanf("%f",&radius);
pi=3.142f;
area=Area(radius);
printf("Area=%f\n",area);
}
