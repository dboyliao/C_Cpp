#include <stdio.h>

int myStrLength(char* str)
{
    int count = 0;
    while (1){
        if (str[count] == '\0') break;
        count += 1;
    }

    return count;
}

int main(int argc, char* argv[])
{
    char* str = "hello";
    printf("%s\n", str);

    if (str[5] == '\0'){
        printf("6th char is null char!\n");
    }

    printf("the string length: %i\n", myStrLength(str));

    return 0;
}
