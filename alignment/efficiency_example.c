#include <stdio.h>
#include <stddef.h>

struct Foo {
    char x;
    double y;
    char z;
};

struct Foo2 {
    char x;
    char z;
    double y;
};

int main(void)
{
    struct Foo f;
    struct Foo2 f2;
    char x = 'x';
    char z = 'z';
    double y = 1;
    f.x = x;
    f.y = y;
    f.z = z;
    f2.x = x;
    f2.y = y;
    f2.z = z;

    printf("size of f: %lu\n", sizeof(f));
    printf("size of f2: %lu\n", sizeof(f2));

    return 0;
}
