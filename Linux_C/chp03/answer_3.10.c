#include<stdio.h>
void	main()
{
int x,y,z,j=0;
printf("Possible plans to buy 100 fowls with 100 Yuan:\n");
for(x=0;x<=20;x++) /*外層循環控制雞翁數*/
for(y=0;y<=33;y++) /*內層循環控制雞母數y在0~33變化*/
{
z=100-x-y; /*內外層循環控制下，雞雛數z的值受x,y的值的制約*/
if(z%3==0 && 5*x+3*y+z/3==100)
/*驗證取z值的合理性及得到一組解的合理性*/
printf("%2d:cock=%2d hen=%2d chicken=%2d\n",++j,x,y,z);
}
}
