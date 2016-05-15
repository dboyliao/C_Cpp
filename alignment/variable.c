#include <stdio.h>
#include <stddef.h>

char *p; // 8 bytes
char c;  // 1 byte
int x;   // 4 bytes

int main(void)
{
    printf("size of *p: %lu\n", sizeof(p));
    printf("size of c: %lu\n", sizeof(c));
    printf("size of x: %lu\n", sizeof(x));
    printf("address of *p: %p\n", &p);
    printf("address of c: %p\n", &c);
    printf("address of x: %p\n", &x);

    return 0;
}
