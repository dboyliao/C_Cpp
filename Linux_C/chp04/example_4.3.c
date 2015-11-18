#include <stdio.h>
int main( void )
{
   FILE *ptr;
   int  i, numread, numwritten,length; 
   length=20;
   char data[length];   
    //向文件test.txt中寫入20個字符    
   if( (ptr = fopen( "test.txt", "w+" )) != NULL )
   {
      for ( i = 0; i < length; i++ )
         data[i] = 'a'+i;      
      numwritten = fwrite(data, sizeof(char), length, ptr );
      printf( "Wrote %d words\n", numwritten );
      fclose( ptr );
   }
   else
      printf( "open file failed!\n" );
   //從文件test.txt中讀取寫入的數據
   if( (ptr = fopen( "test.txt", "r+" )) != NULL )
   {
       numread=fread( data, sizeof(char), length, ptr );      
       printf( "%s\n", data);
       printf( "Read %d words\n", numread );
       fclose( ptr );
   }
   else
      printf( "Can't open the file!\n" );
   return 1;
}
