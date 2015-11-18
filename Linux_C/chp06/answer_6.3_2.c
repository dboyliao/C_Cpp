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
	char write_buf[MEM_BUFSIZE];
	char *mem_ptr;
	
	shm_flags=IPC_CREAT|0666;
	shm_id= shmget((key_t)123,MEM_BUFSIZE,shm_flags);
	
	if(-1==shm_id)
	{
    printf("memory create error.\n");
    exit(EXIT_FAILURE);
	}
	memset(write_buf,0,MEM_BUFSIZE);
	sprintf(write_buf,"Hi,I'm %d.",(int)getpid());
	mem_ptr = (char*)shmat(shm_id, (char *)0, (int)NULL);
	strcat(mem_ptr,write_buf);
	printf("%d write message:%s\n",(int)getpid(),write_buf);
	
	return 0;
}

