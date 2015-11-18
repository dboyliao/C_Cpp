#include <stdio.h>
#include "mysql.h"

int main()
{
 MYSQL mysql;     // need a instance to init
 //MYSQL_RES *res;
 //MYSQL_ROW row;
 //char *query;
 int t,r; // connect the database 
 mysql_init(&mysql);
 if (!mysql_real_connect(&mysql,"localhost", "root", "sun", "student",0,NULL,0))
 {
     printf( "Error connecting to database: %s\n",mysql_error(&mysql));
 }
 else printf("Connected mysql successfully!\n");  
    mysql_close(&mysql);
  
   return 0;
}
