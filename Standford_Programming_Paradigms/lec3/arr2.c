#include <stdlib.h>
#include <stdio.h>

int main(void)
{
    /*
      array == &array[0]
      array + k == &array[k]
    */
    double d = 2;
    int array[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    if (array == &array[0])
    {
        printf("array == &array[0]\n");
    }
    if ((array + 3) == &array[3])
    {
        printf("array + 3 == &array[3]\n");
    }
    *((double *)(array - 1)) = 3.14;
    printf("%i\n", array[0]);
    printf("%g\n", d);
    return EXIT_SUCCESS;
}