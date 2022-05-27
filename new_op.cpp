#include <stdio.h>
#include <stdint.h>

uint8_t pool[10];

class A {
public:
    int x = 10;
    void* operator new(size_t sz) {
        printf("%zu\n", sz);
        return (void *) pool;
    }

    A(){printf("default\n");}
};

int main(void) {
    A* a = new A();

    printf("a: %p\n", a);
    for (size_t i = 0; i < 10; ++i) {
        printf("pool[%zu] %p\n", i, &pool[i]);
    }

    int* ptrx = (int*) pool;
    printf("x: %i\n", *ptrx);
    return 0;
}
