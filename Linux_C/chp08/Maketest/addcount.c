#include "addcount.h"

int addcount(int value, int count)
{
	int i = 1;
	for(;i <= count; i++)
		value = value + i;
	
	return value;
}
