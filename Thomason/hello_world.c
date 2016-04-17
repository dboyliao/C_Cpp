#include <stdio.h>
#include <stdlib.h> // standard library
#include <string.h>

int func(){
    printf("Hello\n");
    return 0;
}

int main(int argc, char const *argv[])
{
    int a;
    float p = 3.14;
    char c = 'p';

    int b[2] = {1, 2};
    int* b_ptr;
    b_ptr = b;

    a = (int) c;

    char d[] = "pop"; // char d[] = {'p', 'o', 'p'}
    
    char *d2 = (char *) malloc(sizeof(char) * 3);
    if (d2 == NULL)
    {
        printf("malloc fail.\n");
        return 1;
    } 
    // strcpy(d2, d);
    strncpy(d2, d, 3);
    printf("d2: %s\n", d2);

    // strcat strncat

    // char msg[3];
    // sprinf(msg, "%s", d2);
    // printf("%s\n", msg);
    // // sprintf()

    char* d_ptr = d;

    printf("%p %c\n", d_ptr, *d_ptr);

    func();
    
    printf("%s %s\n", argv[0], argv[1]);
    printf("%d\n", a);

    free(d2);
    return 0;
}