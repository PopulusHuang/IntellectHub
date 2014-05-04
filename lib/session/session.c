#include <stdio.h>
#include <time.h>
#include <string.h>
#include <fcntl.h>
#include "session.h"
int session_start()
{
	time_t timep;
	char  session_id[SESSION_SIZE];
	char session_name[SESSION_SIZE];
	char buf[TIME_SIZE];
	int fd;
	memset(session_id,0,sizeof(session_id));
	memset(session_name,0,sizeof(session_name));
	memset(buf,0,sizeof(buf));
	/* get system time */
	time(&timep);
	/* use local time as session id */
	sprintf(session_id,"%x",timep);
	printf("Set-Cookie:sesscli=%s;path=/\r\n",session_id);
	sprintf(session_name,"/tmp/sess%s",session_id);
	/* create session file */
	fd = open(session_name,O_CREAT|O_RDWR,0644);
	if(fd < 0)
	{
		printf("CREATE_FAIL");
		return -1;
	}
//	sprintf(buf,"%d",timep);
//	write(fd,buf,strlen(buf));	
	return 0;
}
int session_check(char *session_id)
{
	char session_name[SESSION_SIZE];	
	int fd;
	time_t now_time;
	unsigned int setup_time = 0; 
	time(&now_time);	
	memset(session_name,0,sizeof(session_name));
	sprintf(session_name,"/tmp/sess%s",session_id);
	fd = open(session_name,O_RDWR);
	if (fd < 0)
	{
		printf("LOGIN_AGAIN");
		return -1;
	}
	sscanf(session_id,"%x",&setup_time);
	if(((now_time - setup_time) > SESSION_TIMEOUT)||(now_time < setup_time))
	{
		session_destory(session_id);
		return -1;
	}
//	printf("Set-Cookie:sesscli=%x;path=/\r\n",now_time); /*update cookie*/
	write(session_name,session_id,strlen(session_id));
	return 0;
}
int session_destory(char *session_id)
{
	char cmd[SESSION_SIZE];	
	int fd;
	memset(cmd,0,sizeof(cmd));
//	printf("Set-Cookie:sesscli=;path=/\r\n"); /*clear cookie*/
	sprintf(cmd,"rm /tmp/sess%s",session_id);
	fd = system(cmd);
	if(fd < 0)
	{
		return -1;
	}
	return 0;
}
