#include <string.h> // memcpy
#include <stdlib.h> // malloc
#include <stdio.h>

int main(void) {
    int arr[] = {1, 2, 3};
    int* ptr = (int*) malloc(sizeof(int)*3);
    memset(ptr, 0, sizeof(int)*3);
    printf("%d, %d, %d\n", *ptr, *(ptr+1), *(ptr+2));
    memcpy(ptr, arr, sizeof(int)*3);
    printf("%d, %d, %d\n", *ptr, *(ptr+1), *(ptr+2));

    return 0;
}