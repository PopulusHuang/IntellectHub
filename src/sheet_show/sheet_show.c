#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include "sheet_sql.h"
#include "cgic.h"
#include "device_sql.h"
#define BUF_SIZE 1024
int cgiMain()
{
	int i,n;
	int ret;
	char table[VALUE_SIZE];
	char dev_name[3][DEVNAME_SIZE];
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
	cgiFormString("tb_name",table,VALUE_SIZE-1);
	for(i = 0;i < 3;i++)	
	{
		dev_getNameByHub(db,i+1,dev_name[i]);	
		sheet_row_show(db,table,i+1,dev_name[i]);
	}
	sqlite3_close(db);
}
