
#include <sys/types.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
	int msg_id,msg_flags;
	int reval;
	char send_msg[64];
	
	msg_flags=IPC_CREAT|0666;
	msg_id=msgget((key_t)456,msg_flags);
	
	if(-1==msg_id)
	{
    printf("msg create error.\n");
    exit(EXIT_FAILURE);
	}
	memset(send_msg,0,64);
	sprintf(send_msg,"Hi,I'm %d.",getpid());
	reval=msgsnd(msg_id,send_msg,sizeof(send_msg),0);
	if(-1==reval)
	{
    printf("message send error.\n");
    exit(EXIT_FAILURE);
	}
	else
		printf("Send message:%s\n",send_msg);
	
	return 0;
}
