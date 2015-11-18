
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
	reval=msgrcv(msg_id,send_msg,64,0,0);
	if(-1==reval)
	{
    printf("message send error.\n");
    exit(EXIT_FAILURE);
	}
	else
	  printf("Received msg:%s\n",send_msg);

	reval=msgctl(msg_id,IPC_RMID,0);
	if(-1==reval)
	{
    printf("remove msg queue error\n");
    exit(EXIT_FAILURE);
	}
	
	return 0;
}
