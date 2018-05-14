// http://arjunsreedharan.org/post/69303442896/the-difference-between-arr-and-arr-how-to-find
#include <stdio.h>

int main(void) {
    int arr[5] = {1};
    printf("arr+1: %p\n", arr+1);
    printf("&arr+1: %p\n", &arr+1);

    return 0;
}
