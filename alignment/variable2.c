#include <stdio.h>

char *p;
char c;
short x;

int main(void)
{
    printf("size of p: %lu\n", sizeof(p));
    printf("size of c: %lu\n", sizeof(c));
    printf("size of x: %lu\n", sizeof(x));
    printf("the address of p: %p\n", &p);
    printf("the address of c: %p\n", &c);
    printf("the address of x: %p\n", &x);
    return 0;
}
