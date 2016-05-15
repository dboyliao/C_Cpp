#include <stdio.h>
#include <stdlib.h>

unsigned long maximum = 0;

int main(int argc, char **argv)
{
    unsigned block_sizes[] = {1024 * 1024 * 1024, 1024*1024, 1024, 1};
    // unsigned maximum = 0;

    int index, count;
    for (index = 0; index < 4; ++index){
        printf("index: %i\n", index);
        for (count = 1;;++count){
            printf("current maximum: %lu bytes\n", maximum);
            void *block = malloc( maximum + block_sizes[index]*count );
            
            if (block){
                maximum = maximum + block_sizes[index]*count;
                free(block);
            } else {
                break;
            }
        }
    }

    printf("malloc maximum: %lu bytes.\n", maximum);

    return 0;
}
