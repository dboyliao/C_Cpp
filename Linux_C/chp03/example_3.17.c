
#include <stdio.h>

void  main()
{
  	FILE *fp_in,*fp_out;
  	if((fp_in=fopen("file1.txt","r"))==NULL)           
  	{
printf("can't open file: file1.txt ");  
exit(1);
  	}
  	if((fp_out=fopen("file1_bk.txt","w"))==NULL)       
  	{
		fclose(fp_in);
printf("can't open file: file1_bk.txt ");  
exit(1);
  	}
  	while(!feof(fp_in))                 
  	{
   		fputc(fgetc(fp_in),fp_out);  
  	}
  	fclose(fp_in);      
 	fclose(fp_out);
}
