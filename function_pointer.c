#include <stdio.h>

typedef int (*myFun)(int x, int y);

void helper(myFun afun){
    afun(1, 1);
}

int fun(int x, int y){
    printf("%d %d", x, y);
    return 0;
}

int main(void){
    helper(fun);
    return 0;
}
