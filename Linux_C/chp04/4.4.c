#include<unistd.h>
#include<stdio.h>
#define LEN 50
int main ()
{
  	int size,i;
	char str1[LEN],str2[LEN];//聲明一個字符數組，用來存放文本文件中的數據
	FILE *fp1,*fp2;	
	fp1=fopen("data.txt","r+");//以讀寫的方式打開文件data.txt
	fgets(str1,LEN,fp1);//由鍵盤輸入數據
	for(i=0;i<LEN;i++)
	{
	if(islower(str1[i]))
	str2[i]=toupper(str1[i]);
	else
        str2[i]=tolower(str1[i]);
	}
	fp2=fopen("/home/data.txt","w+");//在目錄/home下創建一個本本文件
	fwrite(str2,sizeof(char),LEN,fp2);   	 
	printf("%s\n",str1);
	printf("%s\n",str2);
	fclose(fp1);
	fclose(fp2);
	return 1;
}
