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
	dev_getNet(db,ip,netmask,gateway);
	printf("ip:%s netmask:%s gateway:%s\n",ip,netmask,gateway);
	sqlite3_close(db);
	return 0;
}
