#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>

struct A {
    char *p;
    char c;
    int x;
};

struct B {
    char *p;
    char c;
    short x;
};

struct C {
    char *p;
    char c;
    long x;
};

struct D {
    char *p;
    long x;
    char c;
};

int main(void) {
    struct A a;
    struct B b;
    struct C cc;
    struct D d;

    char pp = 'p';
    char *p = &pp;
    char c = 'c';
    int x = 1;
    short sh = 1;
    long l = 1;
    a.p = p;
    a.c = c;
    a.x = x;
    b.p = p;
    b.c = c;
    b.x = sh;
    cc.p = p;
    cc.c = c;
    cc.x = l;
    d.p = p;
    d.c = c;
    d.x = l;

    printf("size of char* (A.p): %lu bytes\npadding: %lu.\n", 
            sizeof(a.p), 
            offsetof(struct A, c) - offsetof(struct A, p) - sizeof(a.p));
    printf("size of char (A.c): %lu bytes\npadding: %lu.\n", 
           sizeof(a.c), 
           offsetof(struct A, x) - offsetof(struct A, c) - sizeof(a.c));
    printf("size of int (A.x): %lu bytes\npadding: %lu.\n", 
            sizeof(a.x), 
            sizeof(a) - offsetof(struct A, x) - sizeof(a.x));
    printf("size of struct A: %lu bytes\n", sizeof(a));

    printf("size of char* (B.p): %lu bytes\npadding: %lu.\n", 
            sizeof(b.p), 
            offsetof(struct B, c) - offsetof(struct B, p) - sizeof(b.p));
    printf("size of char (B.c): %lu bytes\npadding: %lu.\n", 
            sizeof(b.c),
            offsetof(struct B, x) - offsetof(struct B, c) - sizeof(b.c));
    printf("size of short (B.x): %lu bytes\npadding: %lu.\n",
            sizeof(b.x),
            sizeof(b) - offsetof(struct B, x) - sizeof(b.x));
    printf("size of struct B: %lu bytes\n", sizeof(b));

    printf("size of char* (C.p): %lu bytes\npadding: %lu.\n",
            sizeof(cc.p), 
            offsetof(struct C, c) - offsetof(struct C, p) - sizeof(cc.p));
    printf("size of char (C.c): %lu bytes\npadding: %lu.\n", 
            sizeof(cc.c),
            offsetof(struct C, x) - offsetof(struct C, c) - sizeof(cc.c));
    printf("size of short (C.x): %lu bytes\npadding: %lu.\n", 
            sizeof(cc.x),
            sizeof(cc) - offsetof(struct C, x) - sizeof(cc.x));
    printf("size of struct C: %lu bytes\n", sizeof(cc));

    printf("size of char* (D.p): %lu bytes\npadding: %lu.\n", sizeof(d.p), offsetof(struct D, p));
    printf("size of char (D.x): %lu bytes\npadding: %lu.\n", 
            sizeof(d.x),
            offsetof(struct D, c) - offsetof(struct D, x) - sizeof(d.x));
    printf("size of short (D.c): %lu bytes\npadding: %lu.\n",
            sizeof(d.c),
            sizeof(d) - offsetof(struct D, c) - sizeof(d.c));
    printf("size of struct B: %lu bytes\n", sizeof(d));

    return 0;
}
