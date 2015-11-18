
#include <stdio.h>

void  main()
{
FILE *fp1,*fp2;
char s[64];

if((fp1=fopen("string1.txt","r"))==NULL)           
{
printf("can't open file: string1.txt");  
exit(1);
}
if((fp2=fopen("string2.txt","a"))==NULL)  
{
	fclose(fp1);
    printf("can't open file: string2.txt\n"); 
exit(1);
}

while(fgets(s,64,fp1)!=NULL) 
{
printf("%s",s);  
    fputs(s,fp2);  
   	fputs("\n",fp2);
}
fclose(fp1);  
fclose(fp2);
}
