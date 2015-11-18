#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define MAXSTACK 100

int stack[MAXSTACK][2];
int size=0;
sem_t sem;
/* 從檔案1.dat讀取數據，每讀一次，信號量加一*/
void ReadData1(void)
{
FILE *fp=fopen("1.dat","r");
while(!feof(fp)){
fscanf(fp,"%d %d",&stack[size][0],&stack[size][1]);
sem_post(&sem);
++size;
}
fclose(fp);
}
/*從檔案2.dat讀取數據*/
void ReadData2(void){
FILE *fp=fopen("2.dat","r");
while(!feof(fp)){
fscanf(fp,"%d %d",&stack[size][0],&stack[size][1]);
sem_post(&sem);
++size;
}
fclose(fp);
}
/*中斷等待緩衝區有數據，讀取數據後，釋放空間，繼續等待*/
void HandleData1(void){
while(1){
sem_wait(&sem);
printf("Plus:%d+%d=%d\n",stack[size][0],stack[size][1],
stack[size][0]+stack[size][1]);
--size;
}
}
void HandleData2(void){
while(1){
sem_wait(&sem);
printf("Multiply:%d*%d=%d\n",stack[size][0],stack[size][1],
stack[size][0]*stack[size][1]);
--size;
}
}
int main(void)
{
pthread_t t1,t2,t3,t4;
sem_init(&sem,0,0);
pthread_create(&t1,NULL,(void *)HandleData1,NULL);
pthread_create(&t2,NULL,(void *)HandleData2,NULL);
pthread_create(&t3,NULL,(void *)ReadData1,NULL);
pthread_create(&t4,NULL,(void *)ReadData2,NULL);
/* 防止程序過早退出，讓它在此無限期等待*/
pthread_join(t1,NULL);
}
