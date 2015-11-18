#include<unistd.h>
#include<stdio.h>
#define SIZE 100
int main ()
{
  	int size;
	char strin[SIZE],strout[SIZE];//聲明一個字符數組，用來存放輸入的數據	
	FILE *stream=fopen("data.txt","w+");//w+表示以讀寫的方式打開文件data.txt
	fgets(strin,SIZE,stdin);//由鍵盤輸入數據
	fwrite(strin,sizeof(char),SIZE,stream);
	rewind(stream);
	//printf("%s\n",strin);
	//size=fread(strout,sizeof(char),SIZE,stream);	
    size=fread(strout, sizeof(char), SIZE, stream );      
    //printf( "%s\n", strout);  

	printf("%s",strout);
	fclose(stream);
	return 1;
}
