#include <stdio.h>
#include "subcount.h"
#include "addcount.h"
int main(int argc, char * argv[])
{
	int value = 0;
	if(argc == 2)
		value = atoi(argv[]);

	value = addcount(value,20);
	printf("value is : %d\n",value);

	value = subcount(value,10);
	printf("value is : %d\n",value);

	return 0;
}
