#include <stdio.h>

int main(void) {
    char c = 0xC0;
    printf("%x\n", c);
    // reinterpret_cast will handle the incompatiple type casting for you
    int* p = reinterpret_cast<int*>(&c);
    printf("%d\n", *p);
    return 0;
}
