#include <stdio.h>

void butler(void);

int main(void)
{
    printf("I'll invoke butler\n");
    butler();
    printf("Yes, bring me some tea and writable DVDs.\n");
}

void butler(void)
{
    printf("You rang, sir?\n");
}
