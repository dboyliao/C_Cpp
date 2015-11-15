#include <stdio.h>

int main(void)
{
    int a, b;
    a = 5;
    b = 2;
    b = a;
    printf("a: %d\nb: %d\n", a, b);
    a = b;
    printf("a: %d\nb: %d\n", a, b);
    return 0;
}
