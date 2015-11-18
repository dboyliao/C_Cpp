#include <sys/types.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define MEM_BUFSIZE 64

int main()
{
	int shm_id,shm_flags;
	int reval;
	
	char *mem_ptr;
	
	shm_flags=IPC_CREAT|0666;
	shm_id= shmget((key_t)123,MEM_BUFSIZE,shm_flags);
	
	if(-1==shm_id)
	{
    printf("memory create error.\n");
    exit(EXIT_FAILURE);
	}
	
	mem_ptr = (char*)shmat(shm_id, (char *)0, (int)NULL);
	
	printf("%d read message:%s\n",(int)getpid(),mem_ptr);
	
	shmctl(shm_id,IPC_RMID,0);
	return 0;
}
