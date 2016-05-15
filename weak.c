#include <stdio.h>
#include <pthread.h>

int pthread_create(
    pthread_t*,
    const pthread_attr_t*,
    void* (*)(void*),
    void*
) __attribute__ ((weak));

int main(void){
    printf("%p\n", &pthread_create);
    if (pthread_create){
        printf("multi!");
    } else {
        printf("single!");
    }
    return 0;
}
