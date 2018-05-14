#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    /* & is always the lowest byte

    big endian: the lowest byte stores the bit corresponding to
        the largest contributions of magnitude.
    0 1 2 3 4 5 6 7 | 8 9 10 11 12 13 14 15

    little endian: 
    7 6 5 4 3 2 1 0 | 15 14 13 12 11 10 9 8 
    */
    double d = 3.1415;
    char ch = *(char *)&d;
    printf("%c\n", ch);

    short s = 45;
    d = *(double *)&s;
    printf("%g\n", d);

    return EXIT_SUCCESS;
}