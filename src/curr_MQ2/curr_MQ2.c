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
int getCurrentTemp(sqlite3 *db,char *currtemp)
{
	int n;
	n = dev_select(db,"currtemp_tb","temp","id","1",currtemp);
	return n;
}
int cgiMain()
{
	char MQ2[BUF_SIZE];
	char temp[BUF_SIZE];	
	char enable[BUF_SIZE];
	memset(MQ2,0,sizeof(MQ2));
	memset(temp,0,sizeof(temp));
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
	dev_getMQ2(db,MQ2,enable);
	dev_select(db,"currtemp_tb","temp","id","1",temp);
//	getCurrentTemp(db,temp);
	int currMQ2=getCurrentMQ2();
	if(currMQ2 > atoi(MQ2))
	{
		system("./daemond/buzzer");	
	}
	printf("%d:%s:%s°C",currMQ2,MQ2,temp);
	return 0;
}
