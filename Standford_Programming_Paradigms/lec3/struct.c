#include <stdlib.h>
#include <stdio.h>

typedef struct _fraction
{
    int num;
    int denum;
} fraction;

int main(void)
{
    fraction fr = {
        .num = 22,
        .denum = 7};

    ((fraction *)&(fr.denum))->num = 12;
    ((fraction *)&(fr.denum))->denum = 33;
    printf("%i\n", fr.denum);                         // 12
    printf("%i\n", ((fraction *)&(fr.denum))->denum); // 33

    return EXIT_SUCCESS;
}