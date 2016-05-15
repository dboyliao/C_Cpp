#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

struct foo1 {
    char *p;
    char c;
    int x;
};

struct foo2 {
    char c;
    char *p;
    int x;
};

int main(void){
    struct foo1 f1;
    struct foo2 f2;
    char c = 'c';
    char *p = &c;
    int x = 1;

    f1.p = p;
    f1.c = c;
    f1.x = x;
    f2.p = p;
    f2.c = c;
    f2.x = x;

    printf("the size of foo1.p (char*): %lu\npadding: %lu.\n", 
           sizeof(f1.p),
           offsetof(struct foo1, c) - offsetof(struct foo1, p) - sizeof(f1.p));
    printf("the size of foo1.c (char): %lu\npadding: %lu.\n",
            sizeof(f1.c),
            offsetof(struct foo1, x) - offsetof(struct foo1, c) - sizeof(f1.c));
    printf("the size of foo1.x (int): %lu\npadding: %lu.\n",
            sizeof(f1.x),
            sizeof(f1) - offsetof(struct foo1, x) - sizeof(f1.x));

    printf("the size of foo2.c (char): %lu\npadding: %lu.\n",
            sizeof(f2.c),
            offsetof(struct foo2, p) - offsetof(struct foo2, c) - sizeof(f2.c));
    printf("the size of foo2.p (char*): %lu\npadding: %lu.\n",
            sizeof(f2.p),
            offsetof(struct foo2, x) - offsetof(struct foo2, p) - sizeof(f2.p));
    printf("the size of foo2.x (int): %lu\npadding: %lu.\n",
            sizeof(f2.x),
            sizeof(f2) - offsetof(struct foo2, x) - sizeof(f2.x));

    return 0;
}
