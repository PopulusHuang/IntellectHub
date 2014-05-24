#include <stdio.h>
#include <stdlib.h>
#include "device_sql.h"
#define VALUE_SIZE 20
int main(void)
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
	for(i = 0;i < 3;i++)	
	{
		if((n = dev_getNameByHub(db,i+1,dev_name[i]))<0)
			printf("%d",n);
		else
			printf("%s\n",dev_name[i]);
	}
	sqlite3_close(db);
	return 0;
}
