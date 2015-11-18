#include "self_string.h"
#include <string.h>
void main()
{
	char str[23];
	self_stringcopy("2323",str);
	printf("str:%s\n",str);
	
	if(self_stringcompare("abc124","abc124",0) == 0)
		printf("equl..\n");

	if(self_stringcompare("abc124","abc123",0) != 0)
		printf("no equl..\n");

	if(self_stringcompare("abc124","ABc123",1) != 0)
		printf("no equl..\n");

	if(self_stringcompare("abc124","ABc124",1) == 0)
		printf("equl..\n");
}
