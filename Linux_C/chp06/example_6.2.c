
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main ()
{
pid_t child_pid;
child_pid = fork();
switch(child_pid)
{
    case -1:
        printf("Create Process Failed!\n");
        break;
    case 0:
printf("Child Process with ID %d!\n", (int) getpid());
        break;
    default:
        printf("Parent Process with ID %d, Child Process ID %d!\n", (int) getpid(), (int) child_pid);
        break;        
}
return 0;
}
