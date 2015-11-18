#include <stdio.h>
#include <stdlib.h>
long filesize(FILE *stream);
void	main()
{	
	long size,pos;
char	ch;
	FILE *fp_in,*fp_out;
if((fp_in =fopen("data.dat","r"))==NULL)  
{
    printf("can't open file stud.dat\n");
    exit(1);
}
if((fp_out =fopen("trans.dat","w"))==NULL)  
{
	fclose(fp_in);
    printf("can't open file trans.dat\n");
    exit(1);
}
pos=0;
size = filesize(fp_in);
while(pos++<size)
{
	fseek(fp_in,-pos,SEEK_END);
	ch=fgetc(fp_in);
	putchar(ch);
	fputc(ch,fp_out);
}
	fclose(fp_in);
fclose(fp_out);
}
long filesize(FILE *stream) 
{ 
   	int curpos, length; 
curpos = ftell(stream); 
fseek(stream, 0L, SEEK_END); 
length = ftell(stream); 
fseek(stream, curpos, SEEK_SET); 
return length; 
}
