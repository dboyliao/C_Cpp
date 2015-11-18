
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#if   defined(__GNU_LIBRARY__)   &&   !defined(_SEM_SEMUN_UNDEFINED)
      /*   union   semun   is   defined   by   including   <sys/sem.h>   */
#else
     /*   according   to   X/OPEN   we   have   to   define   it   ourselves   */
     union   semun{
                    int   val;                      
                    struct   semid_ds   *buf;          
                    unsigned   short   *array;        
                                                                               
                   struct   seminfo   *__buf;       
                };
#endif 

#define SEM_PATHNAME "/tmp/my_sem"

int main(int argc, char *argv[])
{
		int sem_id,sem_key;
    union semun arg_ctl;
		struct sembuf sem_bufinfo;
    int option_get=IPC_CREAT|IPC_EXCL|0666;
    
    sem_key=ftok(SEM_PATHNAME,'x');
    sem_id=semget(sem_key,1,option_get);
    printf("semaphore id=%d.\n", sem_id);
    
    arg_ctl.val=1;
		if(-1==semctl(sem_id,0,SETVAL,arg_ctl))
			perror("semctl SETVAL error.");
		
		printf("value of semaphore at index 0 is %d.\n", semctl(sem_id, 0, GETVAL,arg_ctl));
		  
		sem_bufinfo.sem_num=0;
		sem_bufinfo.sem_op=-1; 
		sem_bufinfo.sem_flg=IPC_NOWAIT; 
		if(-1==semop(sem_id,&sem_bufinfo,1))
			printf("can not op semaphore.\n");
		else
		  printf("value of semaphore at index 0 is %d.\n", semctl(sem_id, 0, GETVAL,arg_ctl));
		if(-1==semctl(sem_id, 0, IPC_RMID,arg_ctl))
			perror("semctl IPC_RMID");
		else
			printf("remove semaphore ok.\n");

        
    return 0;
}
