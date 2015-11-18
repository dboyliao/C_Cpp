#include <stdio.h>
#include "mysql.h"

int main()
{
	MYSQL mysql;     // need a instance to init
	MYSQL_RES *res;
	MYSQL_ROW row;
	char *query;
	int t,r; // connect the database 
	mysql_init(&mysql);
	if (!mysql_real_connect(&mysql,"localhost", "root", "sun", "book",0,NULL,0))
	{
		printf( "Error connecting to database: %s\n",mysql_error(&mysql));
		return 0;
	}
	else 	
		printf("Connected mysql successfully!\n");  		

	query = "select * from book where price<50 AND publisher='清華大學出版社'";
	t = mysql_real_query(&mysql,query,(unsigned int) strlen(query));

	if (t)

	{

		printf("Error making query: %s\n",

			mysql_error(&mysql));

	}

	else printf("[%s] made...\n", query); 
	res = mysql_store_result(&mysql); 
	while(row = mysql_fetch_row(res))

	{

		for(t=0;t<mysql_num_fields(res);t++)

		{

			printf("%s ",row[t]);

		}

		printf("\n");

	}

	mysql_close(&mysql);

	return 0;
}
