#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include "../share/sheet_sql.h"
#include "../../include/cgic.h"
#define BUF_SIZE 1024
int cgiMain()
{
	int i,n;
	int ret;
	char table[20];
    sqlite3 *db;
	/*sqlite open*/
	ret = sqlite3_open("data/devices.db",&db);
	if(ret != SQLITE_OK)
	{
		fputs(sqlite3_errmsg(db),stderr);
		fputs("\n",stderr);
		exit(1);
	}
	/* cgic header */
    cgiHeaderContentType("text/plain");
	cgiFormString("tb_name",table,20);
	sheet_row_show(db,table,1,"电视");	
	sheet_row_show(db,table,2,"电饭锅");
	sheet_row_show(db,table,3,"空闲");
	sheet_row_show(db,table,4,"电脑");

	sqlite3_close(db);
}
