
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <pthread.h>

void *Print_CurrentTime(void);
int main ()
{
	int ret;
	void *thread_result;
	pthread_t new_thread;
	
	ret = pthread_create(&new_thread,NULL,Print_CurrentTime,NULL);
	if (ret != 0) 
	{
    perror("Thread Creation Failed!");
    exit(EXIT_FAILURE);
	}
	printf("Waiting for New thread...\n");
	ret = pthread_join(new_thread, &thread_result);
	if (ret != 0)
	{
    perror("Thread Join Failed!");
    exit(EXIT_FAILURE);
	}
	printf("Thread Joined,returned:%s\n", (char *)thread_result);
	return 0;
}

void *Print_CurrentTime(void)
{
	time_t lt; 
	lt =time(NULL);
    printf ("Current Time: %s",ctime(&lt));
    pthread_exit("New Thread Finished!");
}
