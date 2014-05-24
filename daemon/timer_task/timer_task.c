#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "device_sql.h"
#include "timer_task.h"
#include "pcduino_gpio.h"

#define BUF_SIZE 64
int timer_getCurrent(HUB_TIME *curr_time)
{
	FILE *fp;
	char cmd[BUF_SIZE];
	char buf[BUF_SIZE];

	memset(cmd,0,sizeof(cmd));
	
	sprintf(cmd,"date \"+%%m-%%d-%%Y/%%H:%%M\"");
	fp = popen(cmd,"r");
	if(fgets(buf,BUF_SIZE-1,fp) == NULL)
		return -1;
	sscanf(buf,"%d-%d-%d/%d:%d",
			&curr_time->mon,&curr_time->day,&curr_time->year,
			&curr_time->hour,&curr_time->min);
	return 0;
}
/* verbose time format: Hour:Minute/mon-day-year 
   short time format:  Hour:Minute
*/
int timer_isVerboseFmt(char *timeStr)
{
	if(strstr(timeStr,"/") != NULL) //verbose format
		return 1;
	return 0;
}
int timer_VerboseFmtSUM(HUB_TIME time)
{
		int sum = 0;
		sum = time.hour+time.min+
			time.mon+time.day+time.year;
		return sum;
}
int timer_ShortFmtSUM(HUB_TIME time)
{
		int sum = 0;
		sum = time.hour+time.min;
		return sum;
}
int timer_decideZone(int start,int end,int needle)
{
	/* judge time zone */
	if(start > end)   //time zone out a day e.g 23:00~02:00
	{
		if(needle < end || needle >=start)
			return IN_TIME_ZONE;
		if(needle == end)
			return RIGHT_TIME_ZONE;
	}
	else  //in a day
	{
		if(needle >= start && needle < end   )	
			return IN_TIME_ZONE;
		if(needle == end)
			return RIGHT_TIME_ZONE;
	}
	return OUT_TIME_ZONE;
}
int timer_isTimerZone(char *start_timeStr,char *end_timeStr)
{
	int ret;
	HUB_TIME curr_time,start_time,end_time;
	int start,end,curr;

	timer_getCurrent(&curr_time);

	sscanf(start_timeStr,"%d:%d/%d-%d-%d",&start_time.hour,&start_time.min,&start_time.mon,&start_time.day,&start_time.year);
	sscanf(end_timeStr,"%d:%d/%d-%d-%d",&end_time.hour,&end_time.min,&end_time.mon,&end_time.day,&end_time.year);
	/* sum start time */
	if(timer_isVerboseFmt(start_timeStr) || timer_isVerboseFmt(end_timeStr))
	{
		start = timer_VerboseFmtSUM(start_time);		
		end = timer_VerboseFmtSUM(end_time);
		curr = timer_VerboseFmtSUM(curr_time);
	}
	else
	{
		start = timer_ShortFmtSUM(start_time);	
		end = timer_ShortFmtSUM(end_time);
		curr = timer_ShortFmtSUM(curr_time);
	}
	ret = timer_decideZone(start,end,curr);
	return ret;
}

int timer_hubtask(HUB_TASK *task,int hubId)
{
	int switch_opt; /* 0:trun off switch 1:turn on switch*/
	int time_zone;
	int pin = hubId+2;
	HUB_TIME curr_time,start_time,end_time; 
	
	if(strcmp(task[hubId].enable,"off") == 0)
		return 0;
	switch_opt = atoi(task[hubId].switch_opt);
	time_zone = timer_isTimerZone(task[hubId].Lvalue,task[hubId].Rvalue);
	switch(time_zone)
	{
		case IN_TIME_ZONE: switch_detect(pin,switch_opt);break;
		/* reverse switch */
		case RIGHT_TIME_ZONE: switch_detect(pin,!switch_opt);break;
		default: break;
	}
	return 0;	
}

int timer_run() 
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
		dev_getTask(db,"timer_tb",task,i);
		timer_hubtask(task,i);
	}
	sleep(1);
}
int main(int argc,char **argv)
{
	while(1)
	{
		timer_run();
		sleep(1);
	}
	return 0;
}
