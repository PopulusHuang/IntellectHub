#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cgic.h"
#include "device_sql.h" 
#define BUF_SIZE 10
int cgiMain()
{
	char MQ2[BUF_SIZE];
	char enable[BUF_SIZE];	
	memset(MQ2,0,sizeof(MQ2));
	memset(enable,0,sizeof(enable));

    cgiHeaderContentType("text/plain");
  /* open database */ 
  	sqlite3 *db;
	int ret = sqlite3_open("data/currdev.db",&db);
	if(ret != SQLITE_OK)
	{
		fputs(sqlite3_errmsg(db),stderr);
		fputs("\n",stderr);
		exit(1);
	}
	int n = dev_getMQ2(db,MQ2,enable);

	printf("%s",MQ2,enable);
	return 0;
}
