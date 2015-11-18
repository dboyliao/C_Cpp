
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
    int read_len;
    char client_fifo_name[64];
    char answer_str[64];

		if (access(FIFO_HANDLE_NAME, F_OK) == -1) {
        if (mkfifo(FIFO_HANDLE_NAME, 0777) != 0) {
            fprintf(stderr, "Could not create fifo %s\n", FIFO_HANDLE_NAME);
            exit(EXIT_FAILURE);
        }
    }
    fifo_handle = open(FIFO_HANDLE_NAME, O_RDONLY);
    if (fifo_handle == -1) {
        fprintf(stderr, "Handle fifo failure\n");
        exit(EXIT_FAILURE);
    }

    do {
        read_len = read(fifo_handle, &ps_fifo, sizeof(ps_fifo));
        memset(answer_str,0,64);
        if (read_len > 0) {
            sprintf(answer_str,"hi,%d,I have received the string:'%s'.",ps_fifo.pid,ps_fifo.str);
            printf("received from %d:%s\n",ps_fifo.pid,ps_fifo.str);
        
        		memset(client_fifo_name,0,64);
            sprintf(client_fifo_name,FIFO_CLIENT_NAME, ps_fifo.pid);
            fifo_client = open(client_fifo_name, O_WRONLY);
            ps_fifo.pid = getpid();
            sprintf(ps_fifo.str,answer_str);
           if (fifo_client != -1) {
              write(fifo_client, &ps_fifo, sizeof(ps_fifo));
              close(fifo_client);
           }
       }
    } while (read_len > 0);
    close(fifo_handle);
    unlink(FIFO_HANDLE_NAME);
    exit(EXIT_SUCCESS);
}
