
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define MAX_COUNT	9
pthread_mutex_t mutex;
pthread_cond_t cond;
int count=0;

void AddCount_Odd_Func(void);
void AddCount_Even_Func(void);

int main()
{
    int ret;
		pthread_t odd_thread,even_thread;
		pthread_attr_t thread_attr;
		
		count = 0;
		pthread_mutex_init(&mutex,NULL);
		pthread_cond_init(&cond,NULL);
		ret = pthread_attr_init(&thread_attr);
		if (ret != 0)
		{
			perror("Attribute Creation Failed");
			exit(EXIT_FAILURE);
		} 
		pthread_attr_setdetachstate(&thread_attr,PTHREAD_CREATE_DETACHED); 

		ret=pthread_create(&odd_thread,&thread_attr,(void *)&AddCount_Odd_Func,NULL);
		if(ret != 0)
		{
			perror("Thread Creation Failed");
         	exit(EXIT_FAILURE);
		}
	  ret = pthread_create(&even_thread,&thread_attr,(void *)&AddCount_Even_Func, NULL);
		if (ret != 0)
		{
			perror("Thread Creation Failed");
    	        exit(EXIT_FAILURE);
		}
		while(count<MAX_COUNT);    
    printf("Finished!\n");
    pthread_cond_destroy(&cond);
    pthread_mutex_destroy(&mutex);
    return 0;
}
void AddCount_Odd_Func(void)
{
	pthread_mutex_lock(&mutex);
	while(count<MAX_COUNT)
	{
		if(count%2==1)
		{
			count++;
			printf("AddCount_Odd_Func():count=%d.\n",count);
			pthread_cond_signal(&cond);
		}
		else
			pthread_cond_wait(&cond, &mutex);				
	}
	pthread_mutex_unlock(&mutex);	
}
void AddCount_Even_Func(void)
{
	pthread_mutex_lock(&mutex);
	while(count<MAX_COUNT)
	{
		if(count%2==0)
		{
			count++;
			printf("AddCount_Even_Func():count=%d.\n",count);
			pthread_cond_signal(&cond);
		}
		else
			pthread_cond_wait(&cond, &mutex);				
	}
	pthread_mutex_unlock(&mutex);
}
