#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include "../../include/cgic.h"
#define BUF_SIZE 1024
void insert_row(int hub_id,char *dev_name,char **sqlData)
{
	/* separate each item with '&'*/
	printf("%d|%s|%s|%s|%s&",hub_id,dev_name,sqlData[1],sqlData[2],sqlData[3]);	
}
int timer_sheet_show(sqlite3 *db,int hub_id,char *dev_name)
{
	char sql[BUF_SIZE];	/* SQL sentene */	
	int ret;
	int row,col;
	char *err = 0;
	char **aResult;

	sprintf(sql,"select * from timer_tb where id='%d';",hub_id);
	/* sqlite3 query, the result are stored in a array 
	 * which was the 'aResult' point to*/
	sqlite3_get_table(db,sql,&aResult,&row,&col,&err);
	int i;

	if(row == 0||col ==0) /* empty result */
	{
		return -1;
	}
	insert_row(hub_id,dev_name,aResult+4);
	return 0;
}
int timer_sheet_modify(sqlite3 *db,int hub_id, char *time, char *switch_opt, char *enable_flg) 
{
	
	char sql[BUF_SIZE];
	char *zErrMsg = NULL;
	int ret;
	/*sqlite open*/
	memset(sql,0,sizeof(sql));
	/*
	sprintf(sql,"update timer_tb set time='%s' \
			switch_opt='%c' enable='%s' where id='%d'",
			time,switch_opt,enable_flg,hub_id);
			*/
	sprintf(sql,"update timer_tb set time='%s' where id='%d'",time,hub_id);
	ret = sqlite3_exec(db,sql,NULL,NULL,&zErrMsg);

	sprintf(sql,"update timer_tb set switch_opt='%s' where id='%d'",switch_opt,hub_id);
	ret = sqlite3_exec(db,sql,NULL,NULL,&zErrMsg);
	sprintf(sql,"update timer_tb set enable='%s' where id='%d'",enable_flg,hub_id);
	ret = sqlite3_exec(db,sql,NULL,NULL,&zErrMsg);
	if(ret != SQLITE_OK)
	{
		fprintf(stderr,"SQL error:%s\n",zErrMsg);	
		sqlite3_free(zErrMsg);
		return -1;
	}
	return 0;
}
int cgiMain()
{
	int i,n;
	int ret;
	char id_buf[10];
	char time_buf[20];
	char switch_buf[5];
	char enable_buf[5];
	char cmd[BUF_SIZE];
	memset(id_buf,0,sizeof(id_buf));
	memset(time_buf,0,sizeof(time_buf));
	memset(switch_buf,0,sizeof(switch_buf));
	memset(enable_buf,0,sizeof(enable_buf));
    sqlite3 *db;
	/* *.db must be under the root directory of web server,
	 * and the directory mode of *.db must be 777*/
	ret = sqlite3_open("data/timer.db",&db);
	if(ret != SQLITE_OK)
	{
		fputs(sqlite3_errmsg(db),stderr);
		fputs("\n",stderr);
		exit(1);
	}
	/* cgic header */
    cgiHeaderContentType("text/plain");
	cgiFormString("hub_id",id_buf,10);
	cgiFormString("time",time_buf,20);
	cgiFormString("switch_opt",switch_buf,5);
	cgiFormString("enableBox",enable_buf,5);
	int hub_id=atoi(id_buf);
	n=timer_sheet_modify(db,hub_id,time_buf,switch_buf,enable_buf);
	/*update sheet*/
	if(n==0)
		timer_sheet_show(db,hub_id,"TV");
	else
		printf("-1");
	//printf("%s|%s|%s|%s",id_buf,time_buf,switch_buf,enable_buf);
	sqlite3_close(db);
}
