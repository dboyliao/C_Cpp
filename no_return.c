#include <stdio.h>
#include <time.h>   // time
#include <stdlib.h> // srand

extern void myExit();//__attribute__((noreturn)); // uncomment this will supress the warning


int foo()
{
    srand(time(NULL));
    int r = rand();
    if (r < 0.5)
    {
        myExit();
    }
    else
    {
        return 1;
    }
}
