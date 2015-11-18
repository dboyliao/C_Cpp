
#include <stdio.h>

void	 SwapValues(int *v_ptr1,int *v_ptr2)
{
int temp=* v_ptr1;
if(*v_ptr1<*v_ptr2)
{
*v_ptr1 = *v_ptr2; *v_ptr2= temp;
}
}
void  main()
{
int  a,b;
int  *a_ptr, *b_ptr;
scanf("%d,%d",&a,&b);
a_ptr = &a;
b_ptr = &b;
SwapValues(&a, &b);//等同於SwapValues(a_ptr, b_ptr);
printf("a=%d,b=%d\n" , a,b);// 等同於printf("a=%d,b=%d",*a_ptr, *b_ptr);
}
