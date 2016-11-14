#include <unistd.h>
#include <sys/reboot.h>
#include <stdio.h>

int main(int argc, char* argv[])
{
    printf("RB_AUTOBOOT: %04x\n", RB_AUTOBOOT);
    printf("RB_ASKNAME: %04x\n", RB_ASKNAME);
    printf("RB_DFLTROOT: %04x\n", RB_DFLTROOT);
    printf("RB_HALT: %04x\n", RB_HALT);
    printf("RB_INITNAME: %04x\n", RB_INITNAME);
    printf("RB_NOSYNC: %04x\n", RB_NOSYNC);
    printf("RB_SINGLE: %04x\n", RB_SINGLE);

    return 0;
}
