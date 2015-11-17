// Simple experiment on int types
#include <stdio.h>
#include <limits.h>

int main(void)
{
    int i = 2147483647;
    int i_p1, i_p2;
    unsigned int j = 4294967295;
    unsigned int j_p1, j_p2;

    printf("No other var\n");
    printf("i: %d %d %d\n", i, i+1, i+2);
    printf("j: %u %u %u\n", j, j+1, j+2);

    printf("With other var\n");
    i_p1 = i + 1;
    i_p2 = i + 2;
    j_p1 = j + 1;
    j_p2 = j + 2;

    printf("i: %d %d %d\n", i, i_p1, i_p2);
    printf("j: %u %u %u\n", j, j_p1, j_p2);
   
    printf("INT_MAX: %d\n", INT_MAX);
    return 0;
}
