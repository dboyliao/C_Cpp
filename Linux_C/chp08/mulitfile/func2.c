#include <stdio.h>
#include "func1.h"
#include "func2.h"
void func2print()
{
	printf("In func2,first, call func1:");
	func1print();

	printf("This is func2 print!\n");
}
