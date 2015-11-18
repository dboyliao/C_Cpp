
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define FIFO_HANDLE_NAME  "/tmp/fifo_handle "
#define FIFO_CLIENT_NAME  "/tmp/fifo_client_%d "

struct ps_fifo_struct {
    pid_t  pid;
    char   str[64];
};

int main()
{
    int fifo_handle, fifo_client;
    struct ps_fifo_struct ps_fifo;
    char client_fifo_name[64];

    fifo_handle = open(FIFO_HANDLE_NAME, O_WRONLY);
    if (fifo_handle == -1) {
        fprintf(stderr, "Open handle fifo failed\n");
        exit(EXIT_FAILURE);
    }
    ps_fifo.pid = getpid();
    memset(client_fifo_name,0,64);
    sprintf(client_fifo_name, FIFO_CLIENT_NAME, ps_fifo.pid);
    if (access(client_fifo_name, F_OK) == -1) {
        if (mkfifo(client_fifo_name, 0777) != 0) {
            fprintf(stderr, "Could not create fifo %s\n", client_fifo_name);
            exit(EXIT_FAILURE);
        }
    }

   sprintf(ps_fifo.str, "hi,I'm %d.", ps_fifo.pid); 
   printf("%d sent: \'%s\'.\n ", ps_fifo.pid, ps_fifo.str);
   write(fifo_handle, &ps_fifo, sizeof(ps_fifo));
   fifo_client = open(client_fifo_name, O_RDONLY);
   if(fifo_client != -1) {
       if(read(fifo_client, &ps_fifo, sizeof(ps_fifo)) > 0) 
          printf("received from %d: %s\n",ps_fifo.pid, ps_fifo.str);
       close(fifo_client);
   }

   close(fifo_handle);
   unlink(client_fifo_name);
   exit(EXIT_SUCCESS);
}
