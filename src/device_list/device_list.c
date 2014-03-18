#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../include/cgic.h"
#include "device_sql.h"
int cgiMain()
{
	int n;
	int ret;
    sqlite3 *db;
	cgiHeaderContentType("text/html");
	ret = sqlite3_open("data/devices.db",&db);
	if(ret != SQLITE_OK)
	{
		fputs(sqlite3_errmsg(db),stderr);
		fputs("\n",stderr);
		exit(1);
	}
	dev_sheet_list(db);
}
