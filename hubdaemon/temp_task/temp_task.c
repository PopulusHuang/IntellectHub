#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "device_sql.h"
#include "pcduino_gpio.h"
#define BUF_SIZE 128
#define TEMP_SIZE 5
#define IN_ZONE 1
#define OUT_ZONE 0
int temp_getCurrent(sqlite3 *db,char *currtemp)
{
	int n;
	n = dev_select(db,"currtemp_tb","temp","id","1",currtemp);
	return n;
}
int temp_isZone(int min,int max,int currtemp)
{
	if( currtemp >= min && currtemp <= max)
		return IN_ZONE;	
	return OUT_ZONE;
}
int temp_hubtask(HUB_TASK *task,int hubId,char *currtemp)
{
	int switch_opt; /* 0:trun off switch 1:turn on switch*/
	int temp_zone;
	int min_temp,max_temp;
	int pin = hubId+2;
	HUB_TIME curr_time,start_time,end_time; 
	
	if(strcmp(task[hubId].enable,"off") == 0)
		return 0;
	switch_opt = atoi(task[hubId].switch_opt);
	min_temp = atoi(task[hubId].Lvalue);
	max_temp = atoi(task[hubId].Rvalue);
	temp_zone = temp_isZone(min_temp,max_temp,atoi(currtemp));

	if(temp_zone == IN_ZONE)
		switch_detect(pin,switch_opt);
	return 0;	
}

int temp_run(sqlite3 *db,char *currtemp) 
{
	HUB_TASK task[3];	
	int i;	
	memset(task,0,sizeof(task));
	for(i = 0;i < 3;i++)		
	{
		dev_getTask(db,"temp_tb",task,i);
		temp_hubtask(task,i,currtemp);
		memset(task,0,sizeof(task));
		sleep(1);
	}
}
int main(void)
{
	sqlite3 *db;
	char currtemp[5];
	int ret = sqlite3_open("/var/intellect_hub/www/cgi-bin/data/currdev.db",&db);

	if(ret != SQLITE_OK)
	{
		fputs(sqlite3_errmsg(db),stderr);
		exit(1);
	}
	while(1)
	{
		temp_getCurrent(db,currtemp);
		//printf("current tempurater=%s\n",currtemp);
		temp_run(db,currtemp);
		sleep(1);
	}
	sqlite3_colse(db);
	return 0;
}
