#include <stdio.h>

int main(void)
{
    char ch;

    printf("Please enter a character: ");
    scanf("%c", &ch);
    printf("\n");
    printf("The code for %c is %d.\n", ch, ch);
    if (ch <= 127 && ch >= 0)
    {
        printf("hello!");
    }
    
    return 0;
}
