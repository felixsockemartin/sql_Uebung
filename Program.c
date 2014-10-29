#include <my_global.h>
#include <mysql.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>


bool send_sql(char* sql)
{
	printf("MySQL client version: %s\n", mysql_get_client_info());
	MYSQL *con = mysql_init(NULL);
	if (con == NULL) 
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		return false;
	}

	if (mysql_real_connect(con, "localhost", "fussball", "fcwombat", "Fussball", 0, NULL, 0) == NULL)
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		mysql_close(con);
		return false;
	}
	
	if(mysql_query(con, sql))
	{
		fprintf(stderr, "%s\n", mysql_error(con));
		mysql_close(con);
		return false;
	}
	
	MYSQL_RES *result = mysql_store_result(con);
	int count = mysql_num_fields(result);
	MYSQL_ROW row;
	
	while ((row = mysql_fetch_row(result)))
	{
		for(int i = 0; i < count; i++) 
		{ 
			printf("%s ", row[i] ? row[i] : "NULL"); 

		} 
		printf("\n"); 
	}
	mysql_close(con);
	return true;
}



int main()
{
	char sql[100];
	puts("SQL Statement eingeben:");
	fgets(sql, 100, stdin);
	//sql = "SELECT * FROM Mannschaft";
	send_sql(sql);
	return 0;
}