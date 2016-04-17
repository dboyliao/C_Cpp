#include <stdio.h>

int a = 1;
int *b = &a;

void fun1(int *i){
    printf(" %d ", *i);
}

void fun2(int *i){
    *i = *i + 1;
}

int main(void){
    fun1(&a);
    fun2(&a);
    printf(" %d ", *b);
}
