#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "device_sql.h"
#include "pcduino_gpio.h"
#define BUF_SIZE 128
#define TEMP_SIZE 5
#define IN_ZONE 1
#define OUT_ZONE 0
int temp_getCurrent()
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
int temp_isZone(int min,int max)
{
	int curr = 0;	
	curr = temp_getCurrent(); 
	if( curr >= min && curr <= max)
		return IN_ZONE;	
	return OUT_ZONE;
}
int temp_hubtask(HUB_TASK *task,int hubId)
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
	temp_zone = temp_isZone(min_temp,max_temp);

	if(temp_zone == IN_ZONE)
		switch_detect(pin,switch_opt);
	return 0;	
}

int temp_run() 
{
	HUB_TASK task[3];	
	int i;	
	sqlite3 *db;

	int ret = sqlite3_open("../../www/cgi-bin/data/devices.db",&db);

	if(ret != SQLITE_OK)
	{
		fputs(sqlite3_errmsg(db),stderr);
		exit(1);
	}
	memset(task,0,sizeof(task));
	for(i = 0;i < 3;i++)		
	{
		dev_getTask(db,"temp_tb",task,i);
		temp_hubtask(task,i);
		sleep(1);
	}
}
int main(void)
{
	int currtemp = temp_getCurrent();

	printf("current tempurater=%d\n",currtemp);
	temp_run();
	return 0;
}
