#include <stdio.h>

#define int_ptr int*

int main(int argc, char* argv[])
{
    printf("Hello world\n");
    int_ptr i; // a int* with no memory allocated to it
    void *void_ptr; // equivalent to a void pointer
    int j = 3;
    i = &j; // fix Segment Fault.
    printf("%p\n", i);
    printf("%p\n", void_ptr);
    printf("Before assinment\n");
    *i = 3; // Segment Fault --> due to dereferencing a void pointer
    // See link below for detail
    // http://stackoverflow.com/questions/31445788/dereferencing-void-pointers-with-casting
    printf("After assignment\n");
    printf("%i\n", *i);
    return 0;
}
