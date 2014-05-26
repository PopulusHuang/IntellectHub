#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cgic.h"
#include "device_sql.h" 
#define MQ2_SIZE 50
int cgiMain()
{
	char MQ2[MQ2_SIZE];
	char enable[MQ2_SIZE];	
	memset(MQ2,0,sizeof(MQ2));
	memset(enable,0,sizeof(enable));

    cgiHeaderContentType("text/plain");
    cgiFormString("MQ2",MQ2,MQ2_SIZE-1);
    cgiFormString("enable",enable,MQ2_SIZE-1);
  /* open database */ 
  	sqlite3 *db;
	int ret = sqlite3_open("data/devices.db",&db);
	if(ret != SQLITE_OK)
	{
		fputs(sqlite3_errmsg(db),stderr);
		fputs("\n",stderr);
		exit(1);
	}
	dev_modifyMQ2(db,MQ2,enable);
	int n = dev_getMQ2(db,MQ2,enable);
	printf("%d:%s:%s",n,MQ2,enable);
	return 0;
}
