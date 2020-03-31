#include <stdio.h>

typedef struct _Object {
    struct _Object* ptr_obj;
    int value;
} Object;

Object obj = {
    &obj,
    3
};

int main(int argc, char* argv[]){
    printf("%p\n", obj.ptr_obj);
    printf("%p\n", &obj);
    return 0;
}