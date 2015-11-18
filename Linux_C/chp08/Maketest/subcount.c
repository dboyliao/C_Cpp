#include "subcount.h"
int subcount(int value, int count)
{
	int i = 1;
	for(; i <= count; i++)
	{
		value = value - i;
	}
	
	return value;
}
