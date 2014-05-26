#include <stdio.h>
#include "cgic.h"
#include "device_sql.h"
#include <string.h>
#include <stdlib.h>
#define BUF_SIZE 128
#define TEMP_SIZE 10
int getCurrentMQ2()
{
	FILE *fp;
	char cmd[BUF_SIZE];
	char temp_buf[TEMP_SIZE];

	memset(cmd,0,sizeof(cmd));
	memset(temp_buf,0,sizeof(temp_buf));
	sprintf(cmd,"./get_MQ2");
	fp = popen(cmd,"r");
	if(fgets(temp_buf,TEMP_SIZE-1,fp) == NULL)
		return -1;
	return atoi(temp_buf);
}
int getCurrentTemp()
{
	FILE *fp;
	char cmd[BUF_SIZE];
	char temp_buf[TEMP_SIZE];

	memset(cmd,0,sizeof(cmd));
	memset(temp_buf,0,sizeof(temp_buf));
	sprintf(cmd,"./get_temp");
	fp = popen(cmd,"r");
	if(fgets(temp_buf,TEMP_SIZE-1,fp) == NULL)
		return -1;
	
	return atoi(temp_buf);
}
int cgiMain()
{
	char MQ2[BUF_SIZE];
	char temp[BUF_SIZE];	
	memset(MQ2,0,sizeof(MQ2));

    cgiHeaderContentType("text/plain");
  /* open database */ 
  	sqlite3 *db;
	int ret = sqlite3_open("data/devices.db",&db);
	if(ret != SQLITE_OK)
	{
		fputs(sqlite3_errmsg(db),stderr);
		fputs("\n",stderr);
		exit(1);
	}
	dev_getMQ2(db,MQ2);
	dev_select(db,"currtemp_tb","temp","id","1",temp);
	int currMQ2=getCurrentMQ2();
	printf("%d:%s:%s°C",currMQ2,MQ2,temp);
	return 0;
}
