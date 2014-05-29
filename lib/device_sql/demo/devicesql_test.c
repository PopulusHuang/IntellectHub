#include <stdio.h>
#include <stdlib.h>
#include "device_sql.h"
int main(void)
{
	int i,n;
	int ret;
	char ip[20];
	char netmask[20];
	char gateway[20];

    sqlite3 *db;
	/*sqlite open*/
	ret = sqlite3_open("../../../www/cgi-bin/data/devices.db",&db);
	if(ret != SQLITE_OK)
	{
		fputs(sqlite3_errmsg(db),stderr);
		fputs("\n",stderr);
		exit(1);
	}
	if(dev_modify(db,"device_tb","4d1d13e0","电视","88")<0)
	{
		printf("modify error!");	
		exit(0);
	}
	dev_sheet_list(db);
	sqlite3_close(db);
	return 0;
}
