#include <stdio.h>

void swap(void **a, void **b);

int main(int argc, char const *argv[])
{
    int x[] = {3, 4};
    int y[] = {4, 3};
    swap((void **)&x, (void **)&y);
    printf("%i, %i\n", x[0], x[1]);
    printf("%i, %i\n", y[0], y[1]);
    return 0;
}

void swap(void **a, void **b)
{
    void *t = *a;
    *a = *b;
    *b = t;
}
