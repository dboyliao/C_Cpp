
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex;
int count=0;
char msg_buf[64];
void SetMsg_Func(void);
void PrintMsg_Func(void);

int main()
{
    int ret;
		pthread_t set_thread;

		count = 4;
		pthread_mutex_init(&mutex,NULL);
		ret = pthread_create(&set_thread,NULL, (void *)&SetMsg_Func, NULL);
		if (ret != 0)
		{
			perror("Thread Creation Failed");
         	exit(EXIT_FAILURE);
		}
		PrintMsg_Func();
		ret = pthread_join(set_thread, NULL);
    if (ret != 0) 
    {
        perror("Thread join failed");
        exit(EXIT_FAILURE);
    }
printf("Finished!\n");
pthread_mutex_destroy(&mutex);
    return 0;
}
void SetMsg_Func(void)
{
	while(count>0)
	{
		pthread_mutex_lock(&mutex);
		memset(msg_buf,0,64);
         sprintf(msg_buf,"count=%d.\n",count--);
		pthread_mutex_unlock(&mutex);
		srand((int)time(0));
		sleep(rand()%3);
	}
	pthread_exit(0);
}
void PrintMsg_Func(void)
{
	while(count>=0)
	{
		pthread_mutex_lock(&mutex);
		printf(msg_buf);
		pthread_mutex_unlock(&mutex);
		if(0==count)
    	        break;
		srand((int)time(0));
		sleep(rand()%3);	}
}
