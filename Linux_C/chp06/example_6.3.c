
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main ()
{
pid_t child_pid, pid;
int status;

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
        pid=wait(&status);
        printf("Child Process finished:PID=%d\n",child_pid);
        if(WIFEXITED(status))
            printf("Child Process exited with code %d\n",WEXITSTATUS(status));
        else
            printf("Child Process Terminated Abnormally!\n");
        break;        
}
return 0;
}
