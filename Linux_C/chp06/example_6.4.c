
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/time.h>

void SignalHandle(int signal)
{
	switch(signal)
	{
		case SIGHUP:
			printf("Catch Signal:SIGHUP(%d)\n ",signal);
			break;
		case SIGINT:
			printf("Catch Signal:SIGINT(%d)\n ",signal);
			break;
		case SIGQUIT:
			printf("Catch Signal:SIGHUP(%d)\n ",signal);
			break;
		case SIGALRM:
			printf("Catch Signal:SIGALRM(%d)\n",signal);
			break;
		default:
			printf("Unknown Signal:%d",signal);
			break;
	}
}

int main()
{
	int sec_delay=5;
	
	printf("Current Process ID:%d\n",(int)getpid());
	
	signal(SIGINT,SignalHandle); 
	signal(SIGQUIT,SignalHandle); 
	signal(SIGALRM,SignalHandle);
	
	alarm(sec_delay);
	while(1)pause();
	
	return 0;
}
