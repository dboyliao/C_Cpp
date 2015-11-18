#include <stdio.h>
#include "mysql.h"

int main()
{
 	MYSQL mysql;     // need a instance to init
 	MYSQL_RES *res;
 	MYSQL_ROW row;
 	char* query[5];
 	int t,i; // connect the database 
 	mysql_init(&mysql);
 	if (!mysql_real_connect(&mysql,"localhost", "root", "sun", "book",0,NULL,0))
 	{
     		printf( "Error connecting to database: %s\n",mysql_error(&mysql));
		return 0;
	}
 	else 	
		printf("Connected mysql successfully!\n");	
	query[0] = "insert into book (id,name,author,publisher,price)values(1001,'
C語言程序設計','譚浩強','清華大學出版社',24.00)";
	query[1] = "insert into book (id,name,author,publisher,price)values(1002,' 
C#入門經典(第4版)','(美國)karli Watson (美國)Christian Nagel','清華大學出版社',118.00)";
	query[2]= "insert into book (id,name,author,publisher,price)values(1003,' 
數據結構(C語言版)','嚴蔚敏等 ','清華大學出版社',22.00)";
	query[3]= "insert into book (id,name,author,publisher,price)values(1004,' 
C++Primer Plus<第5版>中文版','(美)普拉塔','人民郵電出版社',72.00)";
	query[4] = "insert into book (id,name,author,publisher,price)values(1005,' 
算法導論(原書第2版)','科曼(Cormen T.H.) (美)等','機械工業出版社',85.00)";
	for(i=0;i<5;i++)
	{
		t = mysql_real_query(&mysql,query[i],(unsigned int) strlen(query[i]));
		if(!t)
			printf("insert data %s successfully\n",query[i]);
	}
    mysql_close(&mysql);
  
   return 0;
}
