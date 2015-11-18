
#include <stdio.h>

long filesize(FILE *stream); 

void main() 
{ 
   	FILE *fp; 
   	fp = fopen("myfile.txt", "r"); 
   	printf("Filesize of myfile. txt is %ld bytes\n", filesize(fp)); 
   	fclose(fp); 
}
long filesize(FILE *stream) 
{ 
   	long curpos, length; 
curpos = ftell(stream); 
fseek(stream, 0L, SEEK_END); 
length = ftell(stream); 
fseek(stream, curpos, SEEK_SET); 
return length; 
}

