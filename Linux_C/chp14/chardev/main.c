#include <stdio.h> 
#include <stdlib.h> 
#include <sys/types.h> 
#include <sys/stat.h> 
#include <unistd.h> 
#include <fcntl.h> 
#include <string.h> 
  
  
int main(void) 
{ 
int testdev; 
int i,rf=0; 
char buf[15]; 
  
memset(buf, 0, sizeof(buf)); 
testdev = open("/dev/chardev",O_RDWR); 
if ( testdev == -1 ) 
{ 
perror("open\n"); 
exit(0); 
} 
  
rf=read(testdev,buf,11); 
if(rf<0) 
perror("read error\n"); 
printf("R:%s\n",buf); 
close(testdev); 
return 0; 
}

