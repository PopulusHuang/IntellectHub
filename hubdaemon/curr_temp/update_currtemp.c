#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "device_sql.h"
#define BUF_SIZE 128
#define TEMP_SIZE 5
int getCurrentTemp(char *temp_buf)
{
	FILE *fp;
	char cmd[BUF_SIZE];

	memset(cmd,0,sizeof(cmd));
	sprintf(cmd,"/home/ubuntu/daemond/get_temp");
	fp = popen(cmd,"r");
	if(fgets(temp_buf,TEMP_SIZE-1,fp) == NULL)
		return -1;
	
	return 0;
}
int update_currtemp(sqlite3 *db,char *currtemp)
{
	int n;
	n = dev_update(db,"currtemp_tb","temp",currtemp,"id","1");
	return n;
}
int main(void)
{
	char currtemp[TEMP_SIZE];
	char outValue[TEMP_SIZE];
	sqlite3 *db;

	int ret = sqlite3_open("/var/intellect_hub/www/cgi-bin/data/currdev.db",&db);

	if(ret != SQLITE_OK)
	{
		fputs(sqlite3_errmsg(db),stderr);
		exit(1);
	}
	while(1)
	{
		getCurrentTemp(currtemp);
		if(strcmp(currtemp,"xx") == 0)
			continue;
//		printf("currtemp:%s\n",currtemp);
		update_currtemp(db,currtemp);
//		dev_select(db,"currtemp_tb","temp","id","1",outValue);
//		printf("update temp:%s success\n",outValue);
		sleep(4);
	}
	return 0;
}
